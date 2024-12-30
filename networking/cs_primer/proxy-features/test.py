import socket
import select

from enum import Enum, auto
import io

"""
  Goals:

    1. We want the abilitiy to accept mutiple connections on the same thread - Done
    2. We want to parse a HTTP Message - done
    3. We want to use high order multiplexing to connect client to upstream and vice versa (two way connection)
    4. Then add features

"""

class HttpState(Enum):
    START = auto()
    HEADERS = auto()
    BODY = auto()
    END = auto()


class HttpMessage(object):
    def __init__(self):
        self.headers = {}
        self.residual = b''
        self.state = HttpState.START
        self.body = b''
        
    def parse(self, data):
        bs = io.BytesIO(self.residual + data)
        self.residual = b''

        if self.state is HttpState.START:
            request_line = bs.readline()
            if request_line[-1:] != b'\n':
                self.residual = request_line
                return
            self.method, self.uri, self.version = \
                request_line.rstrip().split(b' ')
            self.state = HttpState.HEADERS

        if self.state is HttpState.HEADERS:
            while True:
                field_line = bs.readline()
                if not field_line:
                    break
                if field_line[-1:] != b'\n':
                    self.residual = field_line
                    return
                if field_line == b'\r\n' or field_line == b'\n':
                    if self.method == b'GET':
                        self.state = HttpState.END
                    else:
                        self.state = HttpState.BODY
                    break
                field_name, field_value = field_line.rstrip().split(b': ')
                self.headers[field_name.lower()] = field_value

        if self.state is HttpState.BODY:
            self.body += bs.read()

def is_upstream_socket(sock):
   s = sock.getpeername()
   if s[0] == '127.0.0.1' and s[1] == 3005:
      return True
   return False


if __name__ == "__main__":
  ADDR = ('127.0.0.1', 8000)
  UPSTREAM_ADDR = ('127.0.0.1', 3005)

  # create server socket
  server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  server_sock.bind(ADDR)
  server_sock.listen(10)
  print(f'Server listening on {ADDR}')
  # set inputs to select

  inputs = [server_sock]
  outputs = []

  client_upstream_connection = {}
  upstream_client_connection = {}
  http_messages = {} 
  
  # serve client requests indefinitely
  while True:
    readable, writable, exceptions = select.select(inputs, outputs, inputs + outputs) # each iteration set selectable sockets

    for s in readable:
      # if the socket is the server accept request
      if s is server_sock:
        conn, addr = server_sock.accept()
        print(f"Client connection {addr}")
        conn.setblocking(False)
        inputs.append(conn)
      else:
        # if socket is upstream sock 
        # Get client - upstream connection for each readable client socket
        is_upstream = is_upstream_socket(s) 
        
        # if the socket is an upstream connection 
        if is_upstream:
          # Try to get the corresponding client connection
          try:
             client_conn = upstream_client_connection[s]
          except KeyError:
            for client, upstream_conn in enumerate(upstream_client_connection):
              if s is upstream_conn:
                client_conn = client
                break
            upstream_client_connection[s] = client
        # otherwise it's a client connection and we should try to get the upstream connection
        else:
          try:
            upstream_conn = client_upstream_connection[s]
          except KeyError:
            # if there isn't an existing upstream connection create one
            upstream_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            upstream_sock.connect(UPSTREAM_ADDR)
            client_upstream_connection[s] = upstream_sock
            upstream_client_connection[upstream_sock] = s
            upstream_conn = upstream_sock


        # see if we are currently building an HTTP message for socket in question
        try:
           message = http_messages[s]
        except KeyError:
           # if not create request
           message = HttpMessage()
           http_messages[s] = message
        
        # get data from socket
        data = s.recv(4096)
        if data:
          print(f"Recieved {len(data)} bytes from {s.getpeername()}")
          message.parse(data)

          # if this is an upstream socket add client to writables
          if is_upstream and client_conn not in outputs:
             outputs.append(client_conn)
          # or if it isn't add upstream to output if it isn't in there
          elif not is_upstream and upstream_conn not in outputs:
             outputs.append(upstream_conn)
          print(outputs)
          # or if it isn't add upstream to output if it isn't in there
        else:
          # set message state to end
         
          message.state = HttpState.END
    
    for s in writable:
      if is_upstream_socket(s):
        # get client message to send upstream
        message = http_messages[upstream_client_connection[s]]
      else: 
        # get upstream response to send to client
        message = http_messages[client_upstream_connection[s]] 
      
      # If the message is no longer being chunked then create message and send client
      if message.state == HttpState.END:
         
         print(message, "message")
          #  s.close()
          #  del http_messages[s]

          #  del client_upstream_connection[s]
          #  inputs.remove(s)
           
  server_sock.close()




  '''
    What happens when the message is ready to be sent? 

    - We build the message (formatted properly for http)
    - Send the message 
    - How do we determine if we should close the socket? 
      - If it is an upstream socket:
        - Remove from writables but keep socket open and in readables because we want the response
      - if it is a client socket we just wrote to:
        - Check if the  connection is keep-alive:
        - if not close socket
        - Remove socket from writables but make sure it is still in readables 
        - also close the upstream socket associated to it


  '''