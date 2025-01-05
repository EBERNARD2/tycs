import socket
import select
import zlib

from enum import Enum, auto
import io

"""
  Goals:

    1. We want the abilitiy to accept mutiple connections on the same thread - Done
    2. We want to parse a HTTP Message - done
    3. We want to use high order multiplexing to connect client to upstream and vice versa (two way connection) - done
    4. Then add features

    Feature Goals:
        -  Header modfication: - done
            Req:    x-forward-for : <ip addr>
            Res: Foo : Bar
        - Gzip
            Use zlib 
            Take Response from origin server and zip. 
            Alter headers so browser can make sense of response

        - Content Cache:
            in memory cache of upstream response

        - Other? 

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
            try:
              # process requests
              self.method, self.uri, self.version = \
                request_line.rstrip().split(b' ')
            except Exception:
               # process responses
               self.version, self.status, self.msg = request_line.rstrip().split(b' ', 2)
               return
            
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
    def add_header(self, field, value):
      self.headers[bytes(field, 'utf-8')] = bytes(value, 'utf-8')

    def create_message(self):
      output = self.method + b' ' + self.uri + b' ' + self.version + b'\r\n'
      # process headers
      for header in self.headers:
         output = output + header.title() + b": " + self.headers[header] + b"\r\n"
       
      output = output + b'\r\n' + self.body
      return output
         
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
  mem_cache = {}
  accepted_encodings = {}
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

          try:
            send_cache = message.status == b'304'
          except Exception as e:
            send_cache = False

          if not is_upstream and not s in accepted_encodings and not send_cache:
              try:  
                accepted_client_encodings = message.headers[b'accept-encoding']
                accepted_encodings[s] = accepted_client_encodings
              except KeyError:
                 print("Request does not have accept-encoding header")
            
          # if this is an upstream socket add client to writables
          if is_upstream and client_conn not in outputs:
             outputs.append(client_conn)
          # or if it isn't add upstream to output if it isn't in there
          elif not is_upstream and upstream_conn not in outputs:
             outputs.append(upstream_conn)
          # or if it isn't add upstream to output if it isn't in there
        else:
          # set message state to end
          message.state = HttpState.END
           

    for s in writable:      
      writable_upstream_sock = is_upstream_socket(s)
      if writable_upstream_sock:
        # get client message to send upstream
        message = http_messages[upstream_client_connection[s]]
      else: 
        # get upstream response to send to client
        message = http_messages[client_upstream_connection[s]] 
        try:
          message.body =  zlib.compress(message.body)
          message.headers[b"content-length"] = str(len(message.body)).encode()
          message.add_header("content-encoding", "gzip")
        except Exception as e:
          print(f"Error compressing body. Sending uncompressed body... {e}")
       
      
        # If the message is no longer being chunked then create message and send client
      if writable_upstream_sock:
        message.add_header("x-forwarded-for", s.getpeername()[0])

      
      

      if message.state == HttpState.END :
        # check if message is a response or req
        
        # send message  
        try: 
          if message.status == b'304':
             # Tell client that resource hasn't changed
             s.send(b"HTTP/1.1 304 Not Modified\r\n")  
      
        except AttributeError:
          msg = message.create_message()
          s.send(msg)
          print(f'Wrote {len(msg)} bytes to {s.getpeername()}')
        
        # if we just wrote to an upstream socket cleanup
        if writable_upstream_sock:
          # remove socket from outputs and our in memory messages cache
          # Note that we are keeping the socket open in readables since we want to parse the response
          print(f'Cleanup for {s.getpeername()}')
          outputs.remove(s)
          inputs.append(s)
          del http_messages[upstream_client_connection[s]]
        else:
          print(f'Cleanup for {s.getpeername()}')
          # close upstream connection and cleanup
          upstream_sock = client_upstream_connection[s]
          del upstream_client_connection[upstream_sock]
          inputs.remove(upstream_sock)
          upstream_sock.close()

          # close client connection and cleanup      
          del http_messages[client_upstream_connection[s]] 
          del client_upstream_connection[s]
          inputs.remove(s)
          outputs.remove(s)
          s.close() 
      
    for s in exceptions:
      print(s.getpeername(), "exceptions")

  server_sock.close()
