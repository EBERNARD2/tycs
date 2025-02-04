class ReliableTransferProtocol:
  def __init__(self, socket, mode):
    self.socket = socket
    self.mode = mode
    self.connection = None
    pass

  def connect_to_server(self, server): # 3 way handshake
    pass

  def sendmsg(self, msg):
    pass



""""

  High level overview:

     To send message...

      Add seq number 

      ACK Msgs 


      Handshake- Client sends seq number... Server Acks, client ack with seg 1


      - Client start sending messages.

        ** This strategy will be implemented with head of line blocking for simplicity***

        if the client doesn't recieve an ack after x ms (timeout) then it will retry packet

        If server recieves packet out of order it should discard packet

        Continue to do this until msg is sent

        - Same sequence should happen when server is responding

      
      

  Todo:

    (for client)
    - Pass existing socket to RTP
    - verify mode is client
    - connect method to connect to socket
    - sendmsg method to send data to socket
    - general method (for both serv and client) to break up messages into parts
    - when server sends close connection msg close socket


    (for server)
    - When msg comes comes to server we create a socket to communicate (do not worry about multiple connections)
    - Follow handshake seq
    - follow sendmsg strategy for server until file is sent

    - when message is done send close connnection msg


"""