import select
import socket
import sys

from parser import HttpRequest, HttpState


OWN_ADDR = ('0.0.0.0', 8000)
UPSTREAM_ADDR = ('127.0.0.1', 9000)


def log(s):
    print(s, file=sys.stderr)


def should_keepalive(req):
    c = req.headers.get(b'connection')
    if req.version == b'HTTP/1.0':
        return c and c.lower() == b'keep-alive'
    if req.version == b'HTTP/1.1':
        return not (c and c.lower() == b'close')


if __name__ == '__main__':
    listener = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    listener.setblocking(False)
    listener.bind(OWN_ADDR)
    listener.listen(10)

    inputs = [listener]
    outputs = []
    upstream_for_client = {}
    req_for_client = {}

    log(f'Accepting new connections on {OWN_ADDR}')

    while True:  # one per return from select
        readable, _, _ = select.select(inputs, outputs, inputs)

        for s in readable:
            if s is listener:
                client_sock, client_addr = listener.accept()
                log(f'New connection from {client_addr}')
                client_sock.setblocking(False)
                inputs.append(client_sock)
            else:
                try:
                    upstream_sock = upstream_for_client[s]
                except KeyError:
                    upstream_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                    upstream_sock.connect(UPSTREAM_ADDR)
                    log(f'Connected to {UPSTREAM_ADDR}')
                    upstream_for_client[s] = upstream_sock
                try:
                    req = req_for_client[s]
                except KeyError:
                    req = HttpRequest()
                    req_for_client[s] = req

                data = s.recv(4096)
                log(f'-> *    {len(data)}B')
                if data:
                    req.parse(data)
                    upstream_sock.send(data)
                    log(f'   * -> {len(data)}B')
                else:
                    s.close()
                    inputs.remove(s)
                    del upstream_for_client[s]
                    del req_for_client[s]

                if req.state is HttpState.END:
                    while True:
                        res = upstream_sock.recv(4096)
                        log(f'   * <- {len(res)}B')
                        if not res:
                            break
                        s.send(res)
                        log(f'<- *    {len(res)}B')

                    upstream_sock.close()
                    del upstream_for_client[s]
                    del req_for_client[s]

                    if not should_keepalive(req):
                        s.close()
                        inputs.remove(s)

#         except ConnectionRefusedError:
#             client_sock.send(b'HTTP/1.1 502 Bad Gateway\r\n\r\n')
#             log('<- *    BAD GATEWAY')
#         except Exception as msg:
#             log(msg)
#             client_sock.send(b'HTTP/1.1 500 Internal Server Error\r\n\r\n')
#             log('<- *    INTERNAL SERVER ERROR')
#         finally:
#             client_sock.close()

    listener.close()
