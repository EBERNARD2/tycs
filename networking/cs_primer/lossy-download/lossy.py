import struct
import ipaddress

"""
  Reconstruct and image using OSI Model:

  https://en.wikipedia.org/wiki/OSI_model

"""

def output_str(tuple):
  return ''. join(f"{str(val)}." for val in tuple)

with open("lossy.pcap", "rb") as f:
  magic_number, _, _, _, _, snp_len, llh = struct.unpack("<IHHIIII", f.read(24))
  assert magic_number == 0xa1b2c3d4
  # should be an ethernet frame
  assert llh == 1

  count = 0
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
    if mac_dest == (164, 94, 96, 223, 46, 27):
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

      # get ipv4 packet length
      ipv4_len = struct.unpack("!H", packet[16:18])[0]
      protocol = packet[23] & 0xf

      assert protocol == 6 # verifiy packet transmission protocol is TCP 
      source = ipaddress.IPv4Address(packet[26:30])
      dest = ipaddress.IPv4Address(packet[30:34])

      assert source == ipaddress.IPv4Address("192.30.252.154")
      assert dest == ipaddress.IPv4Address("192.168.0.101")


      """
        Get TCP header info - see https://en.wikipedia.org/wiki/Transmission_Control_Protocol

        TCP header starts at byte 34
      """
            


  print(f"{count} packets counted")
