package main

import (
	"fmt"
	"log"
	"strings"
	"syscall"
)

var (
	PORT    = 8888
	ADDR    = [4]byte{127, 0, 0, 1}
	BACKLOG = 20
)

func main() {
	// Create TCP socket
	fd, err := syscall.Socket(syscall.AF_INET, syscall.SOCK_STREAM, syscall.IPPROTO_IP)

	if err != nil {
		log.Fatalf("Error configuring socket. Please run program again")
	}

	// Set socket to localhost at port number
	var sockIo syscall.SockaddrInet4
	sockIo.Port = PORT
	sockIo.Addr = ADDR

	// Bind
	err = syscall.Bind(fd, &sockIo)

	if err != nil {
		log.Fatalf("Error binding to port %d: %v", PORT, err)
	}

	// Start listening on port only allowing 20 request queued at a time
	err = syscall.Listen(fd, BACKLOG)

	if err != nil {
		log.Fatalf(("Error: please try again"))
	}

	fmt.Printf("Listening on port %d...\n", PORT)

	connection(fd)

}

func createResponseJson(buf []byte, length int) {
	// Process string
	for _, line := range strings.Split(string(buf[:length]), "\n") {

		t := strings.SplitN(line, ":", 2)

		if len(t) > 1 {
			fmt.Printf("%s\n\n", t[0])
			fmt.Printf("%s\n\n", t[1])
		}

	}
}

func connection(fileDescriptor int) {
	for {
		// Establish TCP connection with client and create unique socket for two way communication w/ client
		nfd, _, err := syscall.Accept(fileDescriptor)

		if err != nil {
			log.Fatalf("Error connecting to client: %v\n", err)
		}

		// Create buffer to read http header packet
		buff := make([]byte, 1024)

		// Read request headers
		n, err := syscall.Read(nfd, buff)

		if err != nil {
			log.Fatalf("Error reading client msg: %v\n", err)
		}

		// turn http headers into json so browser (the client) can render to page
		createResponseJson(buff[:], n)

		t := []byte("this is a test")

		syscall.Write(nfd, t)

		syscall.Close(nfd)

	}
}
