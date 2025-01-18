import struct



"""
  This file is little endian so we need to unpack the bytes in big endian format


  - Parse pcap header
  - parse per packet header
    - parse link layer packet
    - parse ip header
    - parse tcp 

  
  use pcap-savefile man page

"""

with open("synflood.pcap", "rb") as file:
  """ 
    Reference man page pcap-savefile for pcap header scheme
  """
  # unpack pcap header bytes
  magic_number, major, minor, ts_accuracy, tz_offset, _, llh = struct.unpack("<IHHIIII", file.read(24))

  assert magic_number == 0xa1b2c3d4
  assert major == 2
  assert minor == 4
  assert ts_accuracy == 0
  assert tz_offset == 0


  # this implementation assumes we are using the loopback interface so we need to assert the link layer header is infact 0
  assert llh == 0
  count = 0
  while True:
    pack_header =  file.read(16)
    if len(pack_header) == 0:
      break
    count += 1
    # see pcap --savefile man page
    _, _, pack_len, pack_data_len = struct.unpack("<IIII", pack_header)
    assert pack_len == pack_data_len
    packet = file.read(pack_len)
    #parse packet headers
    """
      Refer to https://en.wikipedia.org/wiki/IPv4#Header
    """
    assert packet[0] == 2 
    version = packet[4] >> 4
    ihl = (packet[4] & 0b1111) << 2
    print(packet[6:24])
    assert version == 4
    assert ihl == 20



    

  print(f"{count} packets parsed")





