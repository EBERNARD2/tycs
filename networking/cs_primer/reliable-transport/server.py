import socket
import reliable_proto

if __name__ == "__main__":
  ADDR =("0.0.0.0", 8000)
  server = reliable_proto.ReliableTransferProtocol()

  server.bind(ADDR)
  server.listen()