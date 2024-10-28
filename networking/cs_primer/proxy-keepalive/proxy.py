import socket
import sys


OWN_ADDR = ('0.0.0.0', 8000)
UPSTREAM_ADDR = ('127.0.0.1', 9000)


def log(s):
    print(s, file=sys.stderr)


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(OWN_ADDR)
s.listen(10)
log(f'Accepting new connections on {OWN_ADDR}')

while True:
    try:
        client_sock, client_addr = s.accept()
        log(f'New connection from {client_addr}')
        data = client_sock.recv(4096)
        log(f'-> *    {len(data)}B')

        upstream_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        upstream_sock.connect(UPSTREAM_ADDR)
        log(f'Connected to {UPSTREAM_ADDR}')
        upstream_sock.send(data)
        log(f'   * -> {len(data)}B')

        while True:
            res = upstream_sock.recv(4096)
            log(f'   * <- {len(res)}B')

            if not res:
                break

            client_sock.send(res)
            log(f'<- *    {len(res)}B')

    except ConnectionRefusedError:
        client_sock.send(b'HTTP/1.1 502 Bad Gateway\r\n\r\n')
        log('<- *    BAD GATEWAY')
    except OSError as msg:
        log(msg)
    finally:
        upstream_sock.close()
        client_sock.close()

s.close()
