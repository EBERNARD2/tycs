package main

import (
	"fmt"
	"log"
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
		log.Fatalf("Unable to create proxy socket: %v", err)
	}

	// clientSocket, err := syscall.Socket(syscall.AF_INET, syscall.SOCK_STREAM, syscall.IPPROTO_IP)

	if err != nil {
		log.Fatalf("Unable to create client socket: %v", err)
	}

	sockIO := syscall.SockaddrInet4{Port: PORT, Addr: ADDR}
	// staticIO := syscall.SockaddrInet4{Port: STATIC_PORT, Addr: ADDR}

	if err = syscall.Bind(proxyFd, &sockIO); err != nil {
		log.Fatalf("Unable to bind to socket: %v", err)
	}

	if err = syscall.Listen(proxyFd, 20); err != nil {
		log.Fatalf("Error configuring socket: %v", err)
	}

	fmt.Printf("Server listening on %v %v", sockIO.Addr, sockIO.Port)

	// Now we should listen an accept calls
	for {
		var httpMsg [4096]byte
		connection, addr, err := syscall.Accept(proxyFd)

		if err != nil {
			log.Fatalf("Error creating TCP connection: %v", err)
		}

		_, err = syscall.Read(connection, httpMsg[:])

		if err != nil {
			log.Fatalf("Error reading TCP message: %v", err)
		}
		fmt.Printf("New connection from %v", addr)

		// create TCP connection with origin static server

		// read HTTP request
		fmt.Println(string(httpMsg[:]))

		syscall.Close(connection)

	}
}
