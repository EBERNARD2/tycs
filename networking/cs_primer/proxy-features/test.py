import socket
import select

from enum import Enum, auto
import io

"""
  Goals:

    1. We want the abilitiy to accept mutiple connections on the same thread - Done
    2. We want to parse a HTTP Message

    3. Then add features

"""

class HttpState(Enum):
    START = auto()
    HEADERS = auto()
    BODY = auto()
    END = auto()


class HttpRequest(object):
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
  client_requests = {} 
  
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
        # Get client - upstream connection for each readable client socket
        try:
          upstream_conn = client_upstream_connection[s]
        except KeyError:
          # if there isn't an existing upstream connection create one
          upstream_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
          upstream_sock.connect(UPSTREAM_ADDR)
          client_upstream_connection[s] = upstream_sock
          upstream_conn = upstream_sock

        # see if we are currently building requests for a socket
        try:
           req = client_requests[s]
        except KeyError:
           # if not create request
           req = HttpRequest()
           client_requests[s] = req
        
        # get data
        data = s.recv(4096)
        if data:
          print(f"Recieved {len(data)} bytes from {s.getpeername()}")
          req.parse(data)
          print(req.headers)
        else:
           # close connection and check if upstream socket is in writable
           s.close()
           del client_requests[s]
           del client_upstream_connection[s]
           inputs.remove(s)


  server_sock.close()




  