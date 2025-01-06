import sys
import socket
import struct
import random

GOOGLE_PUBLIC_DNS = ('8.8.8.8', 53)


# rename to skip question
def skip_name(res, i):
    while True:
        x = res[i]
        # if this is a pointer to rname skip
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
    rtype, rclass, ttl, rdlength = struct.unpack('!HHIH', res[i:i+10])
    ns = res[i+10:i+10+rdlength]
    # get pointer name
    pass

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
    query += struct.pack('!HH', 2, 1) # NS Qtype
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
    # iterate over all answers
    i = skip_name(res, i) # skip name in answer
    rtype, rclass, ttl, rdlength = struct.unpack('!HHIH', res[i:i+10])
    i += 10
    print(res[i:i+rdlength])
    
    nslen = res[i]
    print(res[i+1:i+1+nslen])
    i += nslen+1
    print(res[i])
    assert res[i] == 0xC0
    i += 1

    offset = int(res[i])
    
    while res[offset] != 0x00:
        partlen = int(res[offset])
        partname = res[offset + 1: offset + 1 + partlen]
        print(partname)
        offset += partlen + 1

    # print(res[offset:])
    
    # output = ''

    
    # while i < i + rdlength:
    #     b = res[i]
    #     if b == 0b11000000:
    #         print("found pointer!")
    #         i += 2
    #     else: 
    #         # process NS
    #         nslen = int(b)
    #         output += str(res[i+1:i+1+nslen]) + "."
    #         i += i + 1 + nslen
    #         print(output)
    
    #     i += 1
    # print(output)
        
    # print('.'.join(str(b) for b in ip_addr))


"""
   - Parse name

   - 

"""