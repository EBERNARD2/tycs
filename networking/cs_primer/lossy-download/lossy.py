import struct
import ipaddress

"""
  Reconstruct an image using OSI Model:

  https://en.wikipedia.org/wiki/OSI_model

"""

def output_str(tuple):
  return ''. join(f"{str(val)}." for val in tuple)


http_packets = {}


with open("lossy.pcap", "rb") as f:
  magic_number, _, _, _, _, snp_len, llh = struct.unpack("<IHHIIII", f.read(24))
  assert magic_number == 0xa1b2c3d4
  # should be an ethernet frame
  assert llh == 1

  count = 0
  last_seq_num = None 

  while True:
    pack_header = f.read(16)

    if len(pack_header) == 0:
      break

    """"
      Per packet header as described in man pcap-savefile
    """
    _, _, pack_len, trc_len = struct.unpack("<IIII", pack_header) # per packet header
    
    assert pack_len == trc_len
    # print(pack_len)

    """
      Ethernet II frame 
      see https://en.wikipedia.org/wiki/Ethernet_frame
    """
    
    packet = f.read(pack_len)
    mac_dest = struct.unpack("!BBBBBB", packet[0:6])
    mac_src = struct.unpack("!BBBBBB", packet[6:12])
  
    print(f"Src {output_str(mac_src)} --> Dest {output_str(mac_dest)}")

    # if the client mac address is the destination
    # mac_dest == (164, 94, 96, 223, 46, 27)

    count +=1
    ether_type = struct.unpack("!H", packet[12:14])[0]

    # confirm that this is an IPV4 packet see https://en.wikipedia.org/wiki/EtherType#values
    assert ether_type == 0x0800 

    """
      Parsing IPV4 Header 
        
        see  https://en.wikipedia.org/wiki/IPv4#header
  """
      
    # verify version and ihl from heaers
    version = (packet[14] & 0b11110000) >> 4
    ihl = (packet[14] & 0b00001111)
    assert version == 4
    assert ihl == 5 # meaning header size is 20 bytes
    ip_header_len = (ihl * 32) / 8
    # get ipv4 packet length
    ipv4_len = struct.unpack("!H", packet[16:18])[0]
    protocol = packet[23] & 0xf

    assert protocol == 6 # verifiy packet transmission protocol is TCP 
    source = ipaddress.IPv4Address(packet[26:30])
    dest = ipaddress.IPv4Address(packet[30:34])

    # assert source == ipaddress.IPv4Address("192.30.252.154")
    # assert dest == ipaddress.IPv4Address("192.168.0.101")


    """
        Get TCP header info - see https://en.wikipedia.org/wiki/Transmission_Control_Protocol

        TCP header starts at byte 34

        client send syn with seq number

        server responce with Syn and ACK bits. AWK Number is client seq

        For data, the client will send a seq number

        The server responsed with the seq number as the ack number


        The length of the data section is not specified in the segment header; 
        it can be calculated by subtracting the combined length of the segment 
        header and IP header from the total IP datagram length specified in the 
        IP header
    """
      # Get headers
    src_port, dest_port, seq_num, ack_num, data_offset, flags = struct.unpack("!HHIIBB", packet[34:48])
       
    if src_port == 80:
      tcp_header_size = (data_offset>> 4) * 32; # Specifies the size of the TCP header in 32-bit words
      # get syn and ack bits
      syn_bit = (flags & 0x02) >> 1
      ack_bit = (flags & 0x10) >> 4    
      finish = (flags & 0x01)    

      tcp_packet_len = int(ipv4_len - (tcp_header_size + ip_header_len))

      data_offset = data_offset >> 4

      i = data_offset + 54

      print(syn_bit, ack_bit)
      print(seq_num, ack_num)
      print(f"Data offset: {data_offset}")
      print(f"Port: {src_port}")
      print(f"Finish {finish}")

        
      if not seq_num in http_packets and not syn_bit: 
        http_packets[seq_num] = packet[i: tcp_packet_len]
        
      # parse http message:
      print("---" * 25)

      """"
        What we neeed to get done 
      
      """

      # verify HTTP ports
      # assert src_port == 80
      # assert dest_port == 59295 # client process port
    

      # also need to grab the data offset 

    
  print(f"{count} packets counted")


sorted_seq_numbers = http_packets.keys()
print(sorted_seq_numbers)
http_res =  b""
for key in sorted(http_packets.keys()):
  http_res += http_packets[key]

headers, body = http_res.split(b"\r\n\r\n")
# print(headers.split(b"\n", 1))
print(len(body))

# with open("lossy.jpeg", "wb") as f:
#   f.write(body)