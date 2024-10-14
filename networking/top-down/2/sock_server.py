import socket
import sys
import selectors
import types

sel = selectors.DefaultSelector()

HOST = "127.0.0.1"
PORT = 65432

host, port = sys.argv[1], int(sys.argv[2])
lsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
lsock.bind((host, port))
lsock.listen()
print(f"Listening on {(host, port)}")
lsock.setblocking(False)
sel.register(lsock, selectors.EVENT_READ, data=None)
    
try: 
  while True:
    events = sel.select(timeout=None)
    for key, mask in events:
      if key.data is None:
        accept_wrapper(key.fileobj)
      else:
        service_connection(key, mask)
except KeyboardInterrupt:
  print("Caught keyboad interrupt, exiting")
finally:
  sel.close()