package main

import (
	"fmt"
	"io"
	"log"
	"syscall"
)

var (
	PORT          = 8080
	ADDR          = [4]byte{127, 0, 0, 1}
	UPSTREAM_PORT = 3005
)

func main() {
	fmt.Println("")

	// Create socket
	sock, err := syscall.Socket(syscall.AF_INET, syscall.SOCK_STREAM, syscall.IPPROTO_IP)

	if err != nil {
		log.Fatalf("Error creating socket: %v\n", err)
	}

	// bind to port
	addr := syscall.SockaddrInet4{Port: PORT, Addr: ADDR}
	if syscall.Bind(sock, &addr) != nil {
		log.Fatalf("Error binding to socket port: %s\n", err)
	}

	// listen on port
	err = syscall.Listen(sock, 20)
	if err != nil {
		log.Fatalf("Error creating socket: %v\n", err)
	}

	fmt.Printf("Listening on port %v....\n", addr.Addr)

	defer syscall.Close(sock)
	conn(sock)
}

func conn(fd int) {
	for {
		conn, _, err := syscall.Accept(fd)

		if err != nil {
			log.Fatalf("Error accepeting socket: %v\n", err)
		}

		upstreamAddr := syscall.SockaddrInet4{Port: UPSTREAM_PORT, Addr: ADDR}
		upstreamSock, err := syscall.Socket(syscall.AF_INET, syscall.SOCK_STREAM, syscall.IPPROTO_IP)

		if err != nil {
			log.Fatalf("Error creating upstream socket: %v\n", err)
		}

		if err := syscall.Connect(upstreamSock, &upstreamAddr); err != nil {
			log.Fatalf("Error connecting to upstream socket: %v\n", err)
		}

		fmt.Println("Connected to Upstream server...")

		for {
			msg := make([]byte, 4096)

			fmt.Println("Waiting for message")
			n, err := syscall.Read(conn, msg)

			if err != nil {
				if err == io.EOF {
					break
				}

				fmt.Printf("Error reading from socket: %v\n", err)
				continue
			}

			_, err = syscall.Write(upstreamSock, msg[:n])

			if err != nil {
				fmt.Printf("Error writing upstream: %v\n", err)
				break
			}

			fmt.Println(string(msg))
			fmt.Printf("Wrote %d bytes upstream\n", n)

			fmt.Println("Reading from upstream socket")
			n, err = syscall.Read(upstreamSock, msg[:]) // Read from upstream server

			fmt.Println("Writing Downstream")

			fmt.Print(string(msg))
			_, err = syscall.Write(conn, msg)

			if err != nil {
				fmt.Printf("Error writing downstream: %v\n", err)
				break
			}

			fmt.Printf("Wrote %d bytes downstream\n", n)

		}

	}
}
