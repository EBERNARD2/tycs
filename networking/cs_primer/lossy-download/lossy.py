import struct

"""
  Reconstruct and image 
"""


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
    _, _, pack_len, trc_len = struct.unpack("<IIII", pack_header)
    assert pack_len == trc_len

    count += 1
    # see https://en.wikipedia.org/wiki/Ethernet_frame
    packet = f.read(pack_len)
    
    print(struct.unpack("<BBB", packet[:3]))
    
  



  print(f"{count} packets counted")
