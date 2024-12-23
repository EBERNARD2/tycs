import socket, sys
import select

ADDR = ("0.0.0.0", 8000)
UPSTREAM = ("127.0.0.1", 3005)

def log(err):
  print(err, file=sys.stderr)




sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(ADDR)
sock.listen(20)
log(f"Accepting connections on port {ADDR}")

while True:
  try:
    keepAlive = True
    while keepAlive:

      clientSock, clientAddr = sock.accept()
      log(f'New connection from {clientAddr}')

      data = clientSock.recv(4096)
      log(f'Recieved {data} from {clientAddr}')

      for line in bytes(data).decode("utf-8").split("\r\n"):
        if line.startswith("Connection: "):
          connectionStatus = line.replace("Connection: ", "")
          if connectionStatus != "keep-alive":
            keepAlive = False
          
      upstreamSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
      upstreamSock.connect(UPSTREAM)

      log(f'Connected to upstream server')
      upstreamSock.send(data)
      log(f'Sent {len(data)}B upstream')


      while True:
        res = upstreamSock.recv(4096)
        if not res:
          break
        clientSock.send(res)
        log(f'Sent {len(data)}B to client')

  except ConnectionRefusedError:
    clientSock.send(b'HTTP/1.1 502 Bad Gateway\r\n\r\n')
    log('<- *    BAD GATEWAY')

  finally:
    clientSock.close()
    upstreamSock.close()

sock.close()

