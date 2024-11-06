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

		var msg = make([]byte, 4096)
		n, err := syscall.Read(clientSock, msg)

		if n == 0 {
			continue
		}

		if err != nil {
			log.Printf("Error reading from client socket: %v", err)
			continue
		}

		go connectClientUpstream(clientSock, msg[:n], upstreamAddr)

	}
}

func connectClientUpstream(clientSock int, msg []byte, upstreamAddr syscall.SockaddrInet4) {
	upstreamSocket, err := syscall.Socket(syscall.AF_INET, syscall.SOCK_STREAM, syscall.IPPROTO_IP)

	if err != nil {
		log.Printf("Error creating upstream socket: %v\n", err)
		return
	}

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

		n, err := syscall.Read(upstreamSocket, res)

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
	err = syscall.Close(upstreamSocket)
	if err != nil {
		log.Printf("Error closing upstream socket: %v\n", err)
		return
	}

	err = syscall.Close(clientSock)
	if err != nil {
		log.Printf("Error closing client socket: %v\n", err)
		return
	}

	fmt.Println("Closed upstrean and client sockets")
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
