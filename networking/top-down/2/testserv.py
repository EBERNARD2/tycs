from socket import *
import os


cwd = os.getcwd()
serverSocket = socket(AF_INET, SOCK_STREAM)
port = 8000
serverSocket.bind(('localhost', port))
serverSocket.listen(1)
 
while True:
  print('Ready to serve...')
  connectionSocket, add = serverSocket.accept()
  message = connectionSocket.recv(1024).decode().splitlines()[0]
  if len(message):
    resource_requested = message.split()[1]
    path = cwd + resource_requested

    if os.path.isfile(path):
      fi = open(path, "r")
      data = fi.read()
      if not data:
        break
      while data:
        connectionSocket.send(data.encode())
        data = fi.read()
    else:
      fi = open("404.html", "r")
      if not data:
        break
      while data:
        connectionSocket.send(data.encode())
        data = fi.read()

