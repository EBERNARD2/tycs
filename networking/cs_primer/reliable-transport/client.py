""""

Create socket to proxy server


https://http2-explained.haxx.se/en/part4



"""
import socket

PROXY_ADDR = ('0.0.0.0', 7000)


if __name__ == "__main__":
  sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

  for i in range(20):
    v = f"hey {i}"
    sock.sendto(bytearray(v, "utf8"), PROXY_ADDR)


  pass