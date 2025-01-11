import argparse
import enum
import ipaddress
import socket
import struct
import random
import sys

GOOGLE_PUBLIC_DNS = ('8.8.8.8', 53)


class InvalidCompression(RuntimeError):
    pass


class RClass(enum.Enum):
    IN = 1
    CS = 2
    CH = 3
    HS = 4


class RType(enum.Enum):
    A = 1
    NS = 2
    CNAME = 5
    SOA = 6
    PTR = 12
    MX = 15
    TXT = 16
    AAAA = 28
    ANY = 255


def parse_name(res, i):
    r"""
    Given response data and starting index, parse and return full domain
    name per RFC 1035 section 4.1.4, and return it along with next index.

    >>> parse_name(b'\x06google\x03com\x00', 0)
    ('google.com.', 12)

    >>> parse_name(b'\x06google\x03com\x00\xc0\x00', 12)
    ('google.com.', 14)

    >>> parse_name(b'\x06google\x03com\x00\x03ns1\xc0\x00', 12)
    ('ns1.google.com.', 18)

    >>> parse_name(b'\xc0\x00', 0)
    Traceback (most recent call last):
    InvalidCompression: infinite recursion

    >>> parse_name(b'\xc0\x03', 0)
    Traceback (most recent call last):
    InvalidCompression: offset out of range
    """
    next_i = None  # index at which to continue parsing
    labels = []
    offsets = set()
    while True:
        try:
            b = res[i]
        except IndexError:
            raise InvalidCompression('offset out of range')
        if b & 0b11000000:  # pointer
            if next_i is None:
                next_i = i + 2
            i = ((b & 0b00111111) << 8) | res[i+1]
            if i in offsets:
                raise InvalidCompression('infinite recursion')
            offsets.add(i)
        elif b == 0b00:  # end of labels
            if next_i is None:
                next_i = i + 1
            break
        else:  # one more label
            labels.append(res[i+1:i+1+b])
            i += b + 1
    return (b'.'.join(labels)).decode('utf8') + '.', next_i


def format_rdata(rtype, data, i, rdlength):
    r"""
    >>> format_rdata(RType.A, b'\xff\x80\x01\x00', 0, 4)
    '255.128.1.0'

    >>> format_rdata(RType.AAAA, b'\xff\xff\x80\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01', 0, 16)
    'ffff:8000::1'

    >>> format_rdata(RType.MX, b'\x00\x07\x03foo\x03bar\x00', 0, 11)
    '7 foo.bar.'

    >>> format_rdata(RType.SOA, b'\x03foo\x00\x03bar\x00\x00\x00\x00\x01\x00\x00\x00\x02\x00\x00\x00\x03\x00\x00\x00\x04\x00\x00\x00\x05', 0, 30)
    'foo. bar. 1 2 3 4 5'
    """
    if rtype is RType.A:
        return f'{data[i]}.{data[i+1]}.{data[i+2]}.{data[i+3]}'
    elif rtype is RType.AAAA:
        return str(ipaddress.IPv6Address(data[i:i+rdlength]))
    elif rtype is RType.MX:
        preference = struct.unpack('!H', data[i:i+2])[0]
        name, _ = parse_name(data, i+2)
        return f'{preference} {name}'
    elif rtype in {RType.NS, RType.PTR, RType.CNAME}:
        name, i = parse_name(data, i)
        return name
    elif rtype is RType.SOA:
        mname, i = parse_name(data, i)
        rname, i = parse_name(data, i)
        vals = [mname, rname]
        vals.extend(struct.unpack('!IIIII', data[i:i+20]))
        return ' '.join(str(v) for v in vals)
    elif rtype is RType.TXT:
        return data[i:i+rdlength].decode('utf8')


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('hostname', nargs='?')
    parser.add_argument('rtype', nargs='?', default='A')
    parser.add_argument('-x', dest='reverse')
    parser.add_argument('--test', action='store_true')
    args = parser.parse_args()
    if args.test:
        import doctest
        doctest.testmod()
        print('OK')
        sys.exit(0)
    if args.reverse:
        rtype = RType.PTR
        hostname = '.'.join(reversed(args.reverse.split('.'))) + '.in-addr.arpa'
    else:
        hostname = args.hostname
        try:
            rtype = RType[args.rtype]
        except KeyError:
            rtype = RType.A
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    xid = random.randint(0, 0xffff)
    flags = 0x0100
    query = struct.pack('!HHHHHH', xid, flags, 1, 0, 0, 1)
    qname = b''.join(
        len(p).to_bytes(1, 'big') + p.encode('ascii')
        for p in hostname.split('.')) + b'\x00'
    query += qname
    query += struct.pack('!HH', rtype.value, 1)
    # add OPT pseudo RR to extend UDP payload size, see RFC 6891
    query += b'\x00' + struct.pack('!HHIH', 41, 4096, 0, 0)
    s.sendto(query, GOOGLE_PUBLIC_DNS)
    # loop until we get the response to our answer
    while True:
        res, sender = s.recvfrom(4096)
        if sender != GOOGLE_PUBLIC_DNS:
            continue
        rxid, rflags, qdcount, ancount, _, _ = \
            struct.unpack('!HHHHHH', res[:12])
        if rxid == xid:
            break

    i = 12
    name, i = parse_name(res, i)
    i += 4  # skip qtype and qclass
    for idx in range(ancount):
        name, i = parse_name(res, i)
        rtype, rclass, ttl, rdlength = struct.unpack('!HHIH', res[i:i+10])
        rdata = format_rdata(RType(rtype), res, i+10, rdlength)
        print(f'{name}\t{ttl}\t{RClass(rclass).name}\t{RType(rtype).name}\t{rdata}')
        i += 10 + rdlength
