import socket



class RTPBlock:
  def __init__(self):
    self.data_packets = []
    self.seq_number = None

  def addpacket(self, segment):
    self.data_packets.append(segment)

    # read seq header
  

  
class ReliableTransferProtocol:
  def __init__(self):
    self.hostsocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    self.current_connections = {}
    self.seq_number = None


  def connect(self, addr):
    # implement 3 way handshake
    if addr in self.current_connections:
      raise Exception(f"Connection with {addr} already exists")
    
    connection_block = self.current_connections[addr] = RTPBlock()

    # add handshake seqment
    self.seq_number = 0
    msg = f"syn={self.seq_number} ack=0"
    self.hostsocket.sendto(bytes(msg, "utf-8"), addr)

    while True:
      data, addr = self.hostsocket.recvfrom(4096)
      print(data)
      return
      # get ack 

      
      
    pass

  def bind(self, addr):
    # bind to port
    self.hostsocket.bind(addr)
    print(f"Server listening on port {addr[1]}")


  def listen(self):
    # await udp segments to arrive
    while True:
      data, addr = self.hostsocket.recvfrom(4096)
      # do some work...
      # if the connecttion doesn't exist execute the 3 way handshake
      if not addr in self.current_connections:
        # add connectioon to current connections
        self.current_connections[addr] = RTPBlock()

        print(data)
        return # for now

        # read syn 
      else:
        # add packet to queue
        datablock = self.current_connections[addr]
        datablock.addpacket(data)
        # ack packet

        pass

  def send(self, buffer):
    if self.seq_number is None:
      self.seq_number = 0;
    

    # add sequence number to packet 
    pass

    

""""


  Server

  - create socket
  - bind to socket 



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