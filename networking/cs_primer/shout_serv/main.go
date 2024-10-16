package main

import (
	"fmt"
	"log"
	"os"
	"strings"
	"syscall"
)

var (
	PORT  = 8888
	ADDR  = [4]byte{127, 0, 0, 1}
	BYTES = 1024
)

func main() {
	// Create socket
	serverFd, err := syscall.Socket(syscall.AF_INET, syscall.SOCK_DGRAM, syscall.IPPROTO_IP)

	if err != nil {
		fmt.Printf("There was a problem creating the socket. Please run program again\n")
		os.Exit(1)
	}

	// bind to a port and set loopback address

	var sockIO syscall.SockaddrInet4
	sockIO.Port = PORT
	sockIO.Addr = ADDR

	err = syscall.Bind(serverFd, &sockIO)

	if err != nil {
		fmt.Printf("There was a problem binding to the socket port. Please run program again\n")
		os.Exit(1)
	}

	fmt.Printf("Server ready on port %d...\n", PORT)

	for {
		buff := make([]byte, 1024)

		_, from, err := syscall.Recvfrom(serverFd, buff, syscall.MSG_WAITALL)

		if err != nil {
			log.Fatal("Unable to process message")
		}

		msg := strings.ToUpper(string(buff[:]))

		syscall.Sendto(serverFd, []byte(msg), syscall.MSG_DONTROUTE, from)
	}
}
