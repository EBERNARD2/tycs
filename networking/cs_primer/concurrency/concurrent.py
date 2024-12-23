import socket, sys
import select

ADDR = ("0.0.0.0", 8000)
UPSTREAM = ("127.0.0.1", 3005)


MESSAGE_QUEUES = {}


def log(err):
  print(err, file=sys.stderr)



def main():
  server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  server_sock.setblocking(0)

  server_sock.bind(ADDR)
  server_sock.listen(20)
  log(f"Accepting connections on port {ADDR}")

  # Create sockets to read from 
  inputSockets = [server_sock]
  # Create sockets to write to
  outputSockets = []
  while True:
  # create new select sockets
    readable, writable, exceptions = select.select(inputSockets, outputSockets, server_sock)
    
    for sock in readable:
      if sock is server_sock:
        clientSock, clientAddr = server_sock.accept()
        clientSock.setblocking(0) # Non blocking socket
        log(f'New connection from {clientAddr}')
        inputSockets.append(clientSock)
        MESSAGE_QUEUES[sock] = []
      else:
        data = sock.recv(4096)
        if data:
          log(f'Recieved {data} from {clientAddr}')
          keepAlive = keepAlive(data)
          MESSAGE_QUEUES[sock].append(data)

          if sock not in outputSockets and keepAlive:
            outputSockets.append(sock)

          if not keepAlive:
             inputSockets.remove(sock)
             del MESSAGE_QUEUES[sock]
          
          
        # remove socket if it is not a persistent connection 
    for sock in writable:
      print()

      # check if we have a message to send to writable socket - IN QUEUE 


    try:
      keepAlive = True
      while keepAlive:

        clientSock, clientAddr = server_sock.accept()
        log(f'New connection from {clientAddr}')

        data = clientSock.recv(4096)
        log(f'Recieved {data} from {clientAddr}')

        keepAlive = keepAlive(data)
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
    
  server_sock.close()


def keep_alive(data) -> bool:
  for line in bytes(data).decode("utf-8").split("\r\n"):
    if line.startswith("Connection: "):
      connectionStatus = line.replace("Connection: ", "")
      if connectionStatus != "keep-alive":
        return False



if __name__ == "__main__":
  main()



