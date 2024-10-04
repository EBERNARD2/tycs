from socket import *

serverSocket = socket(AF_INET, SOCK_STREAM)
port = 8000
serverSocket.bind(('localhost', port))
serverSocket.listen(1)
 
while True:
  print('Ready to serve...')
  connectionSocket, add = serverSocket.accept()
  print(connectionSocket)
  message = connectionSocket.recv(1024).decode()
  print(message)


