import struct


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

  server_port = None
  initiated_connections = 0
  acked_connections= 0
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
    assert version == 4
    assert ihl == 20
  
    src_port = struct.unpack("!H",packet[24:26])[0]
    dest_port = struct.unpack("!H",packet[26:28])[0]

    syn_bit = packet[34] & 0x02 >> 1
    ack_bit = packet[34] & 0x10 >> 4

    if dest_port == 80 and syn_bit:
      initiated_connections += 1

    if src_port == 80 and ack_bit:
      acked_connections += 1
    print(f"Src: {src_port} -> Dest: {dest_port}")
  


  print(f"{count} packets parsed")
  print(f"{initiated_connections} connections to server")
  print(f"{acked_connections} acks")
  print(f"{(acked_connections/ initiated_connections) * 100}% of connections were properly ACKED")





