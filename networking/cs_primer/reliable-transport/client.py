""""

Create socket to proxy server


https://http2-explained.haxx.se/en/part4



"""
import reliable_proto
import socket

PROXY_ADDR = ('0.0.0.0', 7000)


if __name__ == "__main__":
  sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

  rtp = reliable_proto.ReliableTransferProtocol(sock, "client")
  rtp.send_msg("hey", ("0.0.0.0", 7000))

  while True:
    data, addr = sock.recvfrom(4096)
    print("got data!", data)

  pass