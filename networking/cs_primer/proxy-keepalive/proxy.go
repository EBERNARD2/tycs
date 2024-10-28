package main

import (
	"fmt"
	"log"
	"os"
	"syscall"
)

var (
	ADDR          = [4]byte{127, 0, 0, 1}
	OWN_PORT      = 4000
	UPSTREAM_PORT = 3005
)

func main() {
	ownSocket := syscall.SockaddrInet4{Port: OWN_PORT, Addr: ADDR}
	sock, err := syscall.Socket(syscall.AF_INET, syscall.SOCK_STREAM, syscall.IPPROTO_IP)

	if err != nil {
		log.Fatalf("Error creating socket: %s\n", err)
	}

	if err = syscall.Bind(sock, &ownSocket); err != nil {
		log.Fatalf("Error binding socket: %s\n", err)
	}

	if err = syscall.Listen(sock, 100); err != nil {
		log.Fatalf("Error listening on socket: %s\n", err)
	}

	fmt.Printf("Sever listening on PORT %d...\n", OWN_PORT)

	acceptConnections(sock)
}

func acceptConnections(socket int) {
	for {
		connection, addr, err := syscall.Accept(socket)

		if err != nil {
			fmt.Fprintf(os.Stderr, "Error establishing socket connection: %s\n", err)
			continue
		}

		fmt.Printf("Established connection with: %v\n", addr)

		var message [4096]byte

		n, err := syscall.Read(connection, message[:])

		if err != nil {
			fmt.Fprintf(os.Stderr, "Error reading from client socket: %s\n", err)
			continue
		}

		connectUpstream(connection, message[:n])

		if err = syscall.Close(connection); err != nil {
			fmt.Fprintf(os.Stderr, "Error closing client socket: %s\n", err)
			continue
		}

	}
}

func connectUpstream(clientConnection int, message []byte) {
	// create upstream socket
	upstreamAddr := syscall.SockaddrInet4{Port: UPSTREAM_PORT, Addr: ADDR}
	upstreamSocket, err := syscall.Socket(syscall.AF_INET, syscall.SOCK_STREAM, syscall.IPPROTO_IP)

	if err != nil {
		fmt.Fprintf(os.Stderr, "Error creating upstream socket: %s\n", err)
		return
	}

	err = syscall.Connect(upstreamSocket, &upstreamAddr)

	if err != nil {
		fmt.Fprintf(os.Stderr, "Error connecting to upstream server: %s\n", err)
		return
	}

	_, err = syscall.Write(upstreamSocket, message[:])

	if err != nil {
		fmt.Fprintf(os.Stderr, "Error writing to upstream server: %s\n", err)
		return
	}

	var res []byte
	buffer := make([]byte, 4096)

	for {
		n, err := syscall.Read(upstreamSocket, buffer)
		res = append(res, buffer[:n]...)

		if n == 0 || n < 4096 {
			break
		}

		fmt.Println("2")

		if err != nil {
			fmt.Fprintf(os.Stderr, "Error reading from upstream socket: %s\n", err)
			break
		}

	}
	_, err = syscall.Write(clientConnection, res[:])

	if err != nil {
		fmt.Fprintf(os.Stderr, "Error writing to client socket: %s\n", err)
		return
	}

	if err = syscall.Close(upstreamSocket); err != nil {
		fmt.Fprintf(os.Stderr, "Error closing upstream socket: %s\n", err)
		return
	}
}
