import sys
import socket
import struct
import random

GOOGLE_PUBLIC_DNS = ('8.8.8.8', 53)


def skip_name(res, i):
    while True:
        x = res[i]
        if x & 0b11000000:
            return i + 2
        if x == 0x00:
            i += 1
            break
        i += x + 1
    return i

def parse_name(res, i):
    """
        Deal with question: (We've already established 
        that we are dealing with one question)

        - Parse name 
        - Parse Type
        - Skip class
        - get Length
        - Print Data with with name

    """
    i = skip_name(res, i) # skip name in answer

    rtype, rclass, ttl, rdlength = struct.unpack('!HHIH', res[i:i+10])
    i += 10

    # print name server

    nsname = b''

    while res[i] != 0xC0 or i > len(res):
        nslen = res[i]
        nsname += res[i+1:i+1+nslen]
        i += nslen+1
        if i >= len(res):
            break
        else:
            nsname += b"."
    
    try:
        # assert byte is a pointer
        assert res[i] == 0xC0
    except AssertionError:
        # else we are out of range
        return
    

    i += 1 
    offset = int(res[i])
    i += 1

    domain_name = b''
    # get name chunks until it terminates
    while res[offset] != 0x00:
        # get location
        partlen = int(res[offset])
        # Location will start with length of value so by pass that and get part
        partname = res[offset + 1: offset + 1 + partlen]
        # add part to domain name
        domain_name += partname + b"."
        # get next offset location
        offset += partlen + 1

        if res[offset] == 0xC0:
            offset = int(res[offset + 1])
        



    print(nsname + domain_name)

    return i

if __name__ == '__main__':
    hostname = sys.argv[1]
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    xid = random.randint(0, 0xffff)
    flags = 0x0100
    query = struct.pack('!HHHHHH', xid, flags, 1, 0, 0, 0)
    qname = b''.join(
        len(b).to_bytes(1, 'big') + b.encode('ascii')
        for b in hostname.split('.')) + b'\x00'
    query += qname
    query += struct.pack('!HH', 2, 1) # Query NS Type
    s.sendto(query, GOOGLE_PUBLIC_DNS)
    # loop until we get the response to our answer
    while True:
        res, sender = s.recvfrom(4096)
        if sender != GOOGLE_PUBLIC_DNS:
            continue
        # headers
        rxid, rflags, qdcount, ancount, _, _ = \
            struct.unpack('!HHHHHH', res[:12])
        if rxid == xid:
            break

    assert qdcount == 1
    i = 12
    i = skip_name(res, i)  # skip name in question
    i += 4  # skip qtype and qclass

    print("ANSWER SECTION:", end="\n\n")
     
    # iterate over all answers
    for _ in range(ancount):
        i = parse_name(res, i)
