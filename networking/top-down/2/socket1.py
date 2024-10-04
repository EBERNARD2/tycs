from socket import AF_INET
from socket import SOCK_DGRAM
import socket

serverName = "hostname"
serverPort = 8080
clientSocket = socket(AF_INET, SOCK_DGRAM)
message = input('Enter a character')
clientSocket.sendto(message.encode(), (serverName, serverPort))
modifiedMessage, serverAddress = clientSocket.recvfrom(2048)
print(modifiedMessage.decode())
clientSocket.close()