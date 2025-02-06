import socket


class ReliableTransferProtocol:
  def __init__(self, socket : socket.socket, mode):
    self.socket = socket
    self.mode = mode
    self.connection = None
    self.seq = 1
    self.packet_queue = []
    self.recieve_buffer = []
    pass

  def __connect_to_server(self, serverADDR): # 3 way handshake
    # send server a syn pack
    self.socket.sendto(b"1", serverADDR)
    
    # if server doesnt respond, retry in 20ms
    pass

  def establish_conn(self, msg, addr):
    print(msg, "onserver")
    self.socket.sendto(b"1Ack", addr)

  def send_msg(self, msg, serverAddr):
    self.__connect_to_server(serverAddr)
    pass

  def rcv_msg(sef, msg):
    pass

  def segment_msg(self, msg):
    pass




""""
  High level overview:

  Step 1 connect client to server



    At the sender:
      - The sender will keep a list of all of its outstanding packets. We’ll call that list
      outstanding_packets; initially it is empty.
      - If len(outstanding_packets) < W, transmit the next packet (call it packet k). Store packet
      k and the current time in outstanding_packets.
      - When an ACK for packet k is received, remove k from outstanding_packets.
      - Periodically check the packets in outstanding_packets; if any were received more than
      RTO seconds ago, re-transmit them.
    
    At the receiver:
      - Send an ACK for every received packet.
      - Save delivered packets — ignoring duplicates — in a local buffer.
      - Keep track of the next packet the receiving application expects. After each reception,
      deliver as many in-order packets as possible.

      
      

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

    

    Client stores messages (breaks it down into segements) and stores in packet queue 

"""