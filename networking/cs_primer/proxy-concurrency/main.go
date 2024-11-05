package main

import (
	"fmt"
	"log"
	"syscall"

	"./httpMessageBuilder"
)

var (
	ADDR          = []byte{127, 0, 0, 1}
	OWN_PORT      = 3030
	UPSTREAM_PORT = 8001
)

func main() {
	sock, err := syscall.Socket(syscall.AF_INET, syscall.SOCK_STREAM, syscall.IPPROTO_IP)

	if err != nil {
		log.Fatal(err)
	}

	var req httpMessageBuilder.HTTPMessage

	fmt.Println(sock)

}
