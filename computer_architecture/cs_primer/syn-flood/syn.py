import struct



with open("synflood.pcap", "rb") as file:
  data = file.read(4).hex()
  print(data)