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
  t_stamp_secs, t_stamp_micro_secs, pack_len, pack_data_len = struct.unpack("<IIII", file.read(16))

  assert struct.unpack("<I",file.read(4))[0] == 2 # confirm that packet is a ipv4 packet
  print(pack_data_len)

  """
    Refer to https://en.wikipedia.org/wiki/IPv4#Header
  """
  b = struct.unpack("<B", file.read(1))[0]
 
  # parse header

  print(b & 0b11110000)



