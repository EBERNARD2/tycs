package main

import (
	"bytes"
	"fmt"
	"log"
	"strings"
	"syscall"
)

var (
	ADDR        = [4]byte{127, 0, 0, 1}
	PORT        = 8001
	STATIC_PORT = 3000
)

func main() {

	proxyFd, err := syscall.Socket(syscall.AF_INET, syscall.SOCK_STREAM, syscall.IPPROTO_IP)

	if err != nil {
		log.Fatalf("Unable to create proxy socket: %v\n", err)
	}

	clientSocket, err := syscall.Socket(syscall.AF_INET, syscall.SOCK_STREAM, syscall.IPPROTO_IP)

	if err != nil {
		log.Fatalf("Unable to create client socket: %v\n", err)
	}

	sockIO := syscall.SockaddrInet4{Port: PORT, Addr: ADDR}
	staticIO := syscall.SockaddrInet4{Port: STATIC_PORT, Addr: ADDR}

	if err = syscall.Bind(proxyFd, &sockIO); err != nil {
		log.Fatalf("Unable to bind to socket: %v\n", err)
	}

	if err = syscall.Listen(proxyFd, 20); err != nil {
		log.Fatalf("Error configuring socket: %v\n", err)
	}

	fmt.Printf("Server listening on %d.%d.%d.%d %v\n",
		sockIO.Addr[0],
		sockIO.Addr[1],
		sockIO.Addr[2],
		sockIO.Addr[3],
		sockIO.Port)

	// Now we should listen an accept calls
	for {
		var httpMsg [4096]byte
		connection, addr, err := syscall.Accept(proxyFd)

		if err != nil {
			log.Fatalf("Error creating TCP connection: %v\n", err)
		}

		_, err = syscall.Read(connection, httpMsg[:])

		if err != nil {
			log.Fatalf("Error reading TCP message: %v\n", err)
		}
		fmt.Printf("New connection from %v\n\n", addr)

		// create TCP connection with origin static server

		// _, err = syscall.Write(clientSocket, []byte("GET / HTTP/1.0\r\n\r\n"))
		err = syscall.Connect(clientSocket, &staticIO)

		if err != nil {
			log.Fatalf("Error connecting to Static server: %v", err)
		}

		// defer closing sockets
		defer syscall.Close(clientSocket)
		defer syscall.Close(connection)

		// read HTTP request
		var req []byte

		for _, headerLine := range bytes.Split(httpMsg[:], []byte{13, 10}) {
			if strings.HasPrefix(string(headerLine), "Host:") {
				// Transform host to be upstream server
				req = append(req, []byte(fmt.Sprintf("Host: %d.%d.%d.%d:%d",
					sockIO.Addr[0],
					sockIO.Addr[1],
					sockIO.Addr[2],
					sockIO.Addr[3],
					STATIC_PORT,
				))...)

			} else {
				req = append(req, headerLine...)
			}

			// Add new line back into request
			end := []byte{13, 10}
			req = append(req, end...)
		}

		// Write request to socket
		_, err = syscall.Write(clientSocket, req)

		if err != nil {
			log.Fatalf("Error writing to static server socket: %s\n", err)
		}

		var res [1024]byte
		_, err = syscall.Read(clientSocket, res[:])

		if err != nil {
			log.Fatalf("Error reading from static server socket: %s\n", err)
		}

		_, err = syscall.Write(connection, res[:])

		if err != nil {
			log.Fatalf("Error reading from static server socket: %s\n", err)
		}

	}
}
