package main

import (
	"fmt"
	"log"
	"syscall"
)

var (
	ADDR          = []byte{127, 0, 0, 1}
	OWN_PORT      = 8080
	UPSTREAM_PORT = 3005
)

func main() {
	sock := createSocket()
	defer syscall.Close(sock)
	bindAndListen(sock)

	upstreamAddr := syscall.SockaddrInet4{Port: UPSTREAM_PORT, Addr: [4]byte(ADDR)}

	for {
		clientSock, clientAddr, err := syscall.Accept(sock)
		if err != nil {
			log.Printf("Error establishing connection with client: %v", err)
			continue
		}
		fmt.Printf("New Connection from %v\n", clientAddr)

		var msg = make([]byte, 1500)
		n, _, err := syscall.Recvfrom(clientSock, msg, 0)

		if n == 0 {
			continue
		}

		if err != nil {
			log.Printf("Error reading from client socket: %v", err)
			continue
		}

		upstreamSocket, err := syscall.Socket(syscall.AF_INET, syscall.SOCK_STREAM, syscall.IPPROTO_IP)

		if err != nil {
			syscall.Close(upstreamSocket)
			continue
		}

		err = syscall.Connect(upstreamSocket, &upstreamAddr)
		if err != nil {
			syscall.Close(upstreamSocket)
			continue
		}

		n, err = syscall.Write(upstreamSocket, msg)

		if err != nil {
			log.Printf("Error sending upstream: %v\n", err)
			syscall.Close(upstreamSocket)
			continue
		}

		syscall.Close(upstreamSocket)

		for {
			var res = make([]byte, 4096)

			n, _, err := syscall.Recvfrom(upstreamSocket, res, 0)

			if n == 0 {
				break
			}

			if err != nil {
				log.Printf("Failure reading from upstream server: %v\n", err)
				continue
			}

			fmt.Printf("Read %d bytes\n", n)

			n, err = syscall.Write(clientSock, res[:n])
			if err != nil {
				log.Printf("Failure writing to client: %v\n", err)
				continue
			}

			fmt.Printf("Wrote %d bytes\n", n)

		}
		// connectClientUpstream(clientSock, msg[:n], upstreamAddr, clientAddr)

	}
}

func connectClientUpstream(clientSock int, msg []byte, upstreamAddr syscall.SockaddrInet4, clientAddr syscall.Sockaddr) {
	upstreamSocket, err := syscall.Socket(syscall.AF_INET, syscall.SOCK_STREAM, 0)

	if err != nil {
		log.Printf("Error creating upstream socket: %v\n", err)
		return
	}
	defer syscall.Close(upstreamSocket)

	err = syscall.Connect(upstreamSocket, &upstreamAddr)
	if err != nil {
		log.Printf("Failure connectiing to port upstream\n")
		return
	}

	n, err := syscall.Write(upstreamSocket, msg)

	fmt.Printf("Wrote %d bytes to upstream\n", n)

	if err != nil {
		log.Printf("Error sending upstream: %v\n", err)
		return
	}

	for {
		var res = make([]byte, 4096)

		n, _, err := syscall.Recvfrom(upstreamSocket, res, 0)

		if n == 0 {
			break
		}

		if err != nil {
			log.Printf("Failure reading from upstream server: %v\n", err)
			continue
		}

		fmt.Printf("Read %d bytes\n", n)

		n, err = syscall.Write(clientSock, res[:n])
		if err != nil {
			log.Printf("Failure writing to client: %v\n", err)
			continue
		}

		fmt.Printf("Wrote %d bytes\n", n)

	}

}

func bindAndListen(sock int) {
	proxyAddr := syscall.SockaddrInet4{Port: OWN_PORT, Addr: [4]byte(ADDR)}

	err := syscall.Bind(sock, &proxyAddr)
	if err != nil {
		log.Fatal(err)
	}

	err = syscall.Listen(sock, 50)
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("Server listening on port %d...\n", proxyAddr.Port)
}

func createSocket() int {
	sock, err := syscall.Socket(syscall.AF_INET, syscall.SOCK_STREAM, syscall.IPPROTO_IP)
	if err != nil {
		log.Fatal(err)
	}
	return sock
}
