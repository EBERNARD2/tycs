import socket
import reliable_proto

if __name__ == "__main__":
  ADDR =("0.0.0.0", 8000)

  server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
  connections = {}

  server.bind(ADDR)

  print(f"Server listening on port {ADDR[1]}")

  while True:
    data, addr = server.recvfrom(4096)
    if not addr in connections:
      rtp = reliable_proto.ReliableTransferProtocol(server, "server")
      connections[addr] = rtp
      rtp.establish_conn(data, addr)
      
      pass
    print(data, addr)