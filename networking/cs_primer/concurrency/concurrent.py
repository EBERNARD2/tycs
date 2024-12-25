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
  serverSock.setblocking(False)

  serverSock.bind(ADDR)
  serverSock.listen(20)
  log(f"Accepting connections on port {ADDR}")

  upstreamSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  upstreamSock.setblocking(False)

  try:
    upstreamSock.connect(UPSTREAM)
  except Exception as e:
    print(f"Error {e}")
  finally:
    log(f"Connected to upstream socket on {UPSTREAM}")



  # Create sockets to read from 
  inputSockets = [serverSock, upstreamSock]
  # Create sockets to write to
  outputSockets = []


  while True:
  # create new select sockets
    readable, writable, exceptions = select.select(inputSockets, outputSockets, inputSockets)
    
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
          print(data[len(data) - 2:], "len")

          writableSock = MESSAGE_QUEUES["downstream_socket_addresses"].get()
          print(writableSock, 'writable socket')
          if not writableSock in MESSAGE_QUEUES:
            MESSAGE_QUEUES[writableSock] = queue.Queue()
          
          MESSAGE_QUEUES[writableSock].put(data)
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
          if not upstreamSock in MESSAGE_QUEUES:
            MESSAGE_QUEUES[upstreamSock] = queue.Queue()
          
          MESSAGE_QUEUES[upstreamSock].put(data)
          # Add socket to downstream queue
          MESSAGE_QUEUES["downstream_socket_addresses"].put(sock)
      

    for sock in writable:
      # If there are messages in the queue for this socket send them to socket
      if sock in MESSAGE_QUEUES and not MESSAGE_QUEUES[sock].empty():
          # Add upstream socket to inputs
          for msg in MESSAGE_QUEUES[sock].queue:
            log(f'Writing {len(msg)} bytes to socket: {sock.getsockname()}')
            sock.send(msg)
          del MESSAGE_QUEUES[sock]
      else:
        # Else remove socket
        outputSockets.remove(sock)

    for sock in exceptions:
      print(f"Handling exception for", sock.getpeername())
      if not sock is serverSock or not sock is upstreamSock:
        inputSockets.remove(sock)

        if sock in outputSockets:
          outputSockets.remove(sock)
        sock.close()
        del MESSAGE_QUEUES[sock]

  serverSock.close()
  upstreamSock.close()
      

def more_chunks(data, currentChunkLen):
  for line in data.decode("utf-8").split("\r\n"):
    if line.startswith("Content-Length"):
      totalChunkLen = int(line.split("Content-Length: ")[0]) 
  
      if totalChunkLen - currentChunkLen > 0:
        return True
  return False
      


def keep_alive(data) -> bool:
  for line in bytes(data).decode("utf-8").split("\r\n"):
    if line.startswith("Connection: "):
      connectionStatus = line.replace("Connection: ", "")
      if connectionStatus != "keep-alive":
        return False
  return True



if __name__ == "__main__":
  main()





