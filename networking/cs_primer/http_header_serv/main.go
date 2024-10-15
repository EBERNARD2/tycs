package main

import (
	"fmt"
	"log"
	"syscall"
)

var (
	PORT    = 8888
	ADDR    = []byte{127, 0, 0, 1}
	BACKLOG = 20
)

func main() {
	fd, err := syscall.Socket(syscall.AF_INET, syscall.SOCK_STREAM, syscall.IPPROTO_IP)

	if err != nil {
		log.Fatalf("Error configuring socket. Please run program again")
	}

	var sockIo syscall.SockaddrInet4
	sockIo.Port = PORT
	sockIo.Port = PORT

	err = syscall.Bind(fd, &sockIo)

	if err != nil {
		log.Fatalf("Error binding to port %s: %v", PORT, err)
	}

	err = syscall.Listen(fd, BACKLOG)

	if err != nil {
		log.Fatalf(("Error: please try again"))
	}

	fmt.Printf("Listening on port %d...\n", PORT)

	for {
		err := syscall.Connect(fd, &sockIo)

		if err != nil {
			fmt.Errorf("Error connecting to client: %v", err)
		}

	}

}
