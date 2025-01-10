import sys
import socket
import struct
import random
import ipaddress

GOOGLE_PUBLIC_DNS = ('8.8.8.8', 53)


def parse_name(res, i):
    """
    Given response data and starting index, parse and return full domain
    name per RFC 1035 section 4.1.4, and return it along with next index.
    """
    next_i = None  # index at which to continue parsing
    labels = []
    offsets = set()
    while True:
        if i >= len(res):
            break
        b = res[i]
        if b & 0b11000000:  # pointer
            if next_i is None:
                next_i = i + 2
            i = ((b & 0b00111111) << 8) | res[i+1]
            if i in offsets:
                break  # TODO better way of communicating infinite loop
            offsets.add(i)
        elif b == 0b00:  # end of labels
            if next_i is None:
                next_i = i + 1
            break
        else:  # one more label
            labels.append(res[i+1:i+1+b])
            i += b + 1
    return b'.'.join(labels), next_i

def parse_ipv6(res, i):
    pass

if __name__ == '__main__':
    if "-x" in sys.argv:
        try:
            hostname = sys.argv[2]        
            rtype = 12 # set PTR QTYPE - RFC 1035 Section 3.2.2
        except Exception:
            print("Invalid option: -x")
            print("Usage: dns_client.py -x [ip address]")
            sys.exit(1)
    else:
        hostname = sys.argv[1]
        try:
            rtype = {
                'A': 1,
                'NS': 2,
                'CNAME': 5,
                'SOA': 6,
                'MX': 15,
                'TXT': 16,
                'AAAA': 28
            }[sys.argv[2]]
        except Exception:
            rtype = 1
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    xid = random.randint(0, 0xffff)
    flags = 0x0100
    query = struct.pack('!HHHHHH', xid, flags, 1, 0, 0, 0)

    if rtype == 12:
        parts = hostname.split(".")
        hostname = ''
        for i in range(len(parts) - 1, -1, -1):
            hostname += parts[i]
            if i != 0:
                hostname += '.'
        hostname += '.in-addr.arpa'
            
        pass
    qname = b''.join(
        len(p).to_bytes(1, 'big') + p.encode('ascii')
        for p in hostname.split('.')) + b'\x00'
    query += qname

    query += struct.pack('!HH', rtype, 1)
    s.sendto(query, GOOGLE_PUBLIC_DNS)
    # # loop until we get the response to our answer
    while True:
        res, sender = s.recvfrom(4096)
        if sender != GOOGLE_PUBLIC_DNS:
            continue
        rxid, rflags, qdcount, ancount, nscount, arcount = \
            struct.unpack('!HHHHHH', res[:12])
        if rxid == xid:
            break


    # Skip headers
    i = 12

    # Skip question section
    name, i = parse_name(res, i)
    i += 4  # skip qtype and qclass

    print(ancount, nscount, arcount)
    # Answer Section
    for idx in range(ancount):
      name, i = parse_name(res, i)
      rtype, rclass, ttl, rdlength = struct.unpack('!HHIH', res[i:i+10])
      if rtype == 1:
          ip_addr = res[i+10:i+10+rdlength]
          print('.'.join(str(b) for b in ip_addr))
      elif rtype in [2,6,12]:
          name, i = parse_name(res, i+10)
          print(name)
      elif rtype == 15:
          name, i = parse_name(res, i+12)
          print(name)
      elif rtype == 28:
          print(str(ipaddress.IPv6Address(res[i+10:i+10+rdlength])))
          

    # Name Server Authority section 
    for idx in range(nscount):
      name, i = parse_name(res, i)
      rtype, rclass, ttl, rdlength = struct.unpack('!HHIH', res[i:i+10])

      if rtype == 6: # if the rr is a start of authroitiy server
        name, i = parse_name(res, i+10)
        print(name)


    if rtype == 16:
      rtype, rclass, ttl, rdlength = struct.unpack('!HHIH', res[i:i+10])
      
    
        

      