""""

Create socket to proxy server


https://http2-explained.haxx.se/en/part4



"""
import reliable_proto
import socket

PROXY_ADDR = ('0.0.0.0', 7000)


if __name__ == "__main__":
  socket = reliable_proto.ReliableTransferProtocol()
  socket.connect(PROXY_ADDR)


  pass