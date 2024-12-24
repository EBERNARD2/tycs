import socket, sys
import select, queue

ADDR = ("0.0.0.0", 8000)
UPSTREAM = ("127.0.0.1", 3005)

MESSAGE_QUEUES = {
  "downstream_socket_addresses": queue.Queue()
}




def log(err):
  print(err, file=sys.stderr)


def main():
  serverSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  serverSock.setblocking(0)

  serverSock.bind(ADDR)
  serverSock.listen(20)
  log(f"Accepting connections on port {ADDR}")

  upstreamSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  upstreamSock.setblocking(0)
  upstreamSock.bind(UPSTREAM)

  log(f"Connected to upstream socket on {UPSTREAM}")

  # Create sockets to read from 
  inputSockets = [serverSock]
  # Create sockets to write to
  outputSockets = []

  while True:
  # create new select sockets
    readable, writable, exceptions = select.select(inputSockets, outputSockets, serverSock)
    
    for sock in readable:
      # Accept connections if the socket is the server socket
      if sock is serverSock:
        clientConn, clientAddr = serverSock.accept()
        log(f'New connection from {clientAddr}')
        clientConn.setblocking(0)
        inputSockets.append(clientConn)
        MESSAGE_QUEUES[clientConn] = queue.Queue()
      elif sock is upstreamSock:
        # If upstream socket has data write to next available client socket
        data = upstreamSock.recv(4096)
        if data:
          log(f'Read {len(data)} bytes from upstream server')

          writableSock = MESSAGE_QUEUES["downstream_socket_addresses"].get()
          MESSAGE_QUEUES[writableSock].append(data)
          outputSockets.append(writableSock)
      else:
        # Else read client socket
        data = sock.recv(4096)
        if data:
          log(f'Read {len(data)} bytes from {sock.getsockname()}')
          # Push upstream socket into writables
          if not upstreamSock in outputSockets:
            outputSockets.append(upstreamSock)
          # Add client request to upstream socket writable
          MESSAGE_QUEUES[upstreamSock].append(data)
          # Add socket to downstream queue
          MESSAGE_QUEUES["downstream_socket_addresses"].put(sock)
      

    for sock in writable:
      # If there are messages in the queue for this socket send them to socket
      if len(MESSAGE_QUEUES[sock]) > 0:
          for msg in MESSAGE_QUEUES[sock]:
            log(f'Writing {len(msg)} bytes to socket: {sock.getsockname()}')
            sock.send(msg)
      else:
        # Else remove socket
        outputSockets.remove(sock)

    for sock in exceptions:
      print()
 


        


def keep_alive(data) -> bool:
  for line in bytes(data).decode("utf-8").split("\r\n"):
    if line.startswith("Connection: "):
      connectionStatus = line.replace("Connection: ", "")
      if connectionStatus != "keep-alive":
        return False
  return True



if __name__ == "__main__":
  main()





