package main

import (
	"fmt"
	"log"
	"syscall"
)

func main() {
	sock, err := syscall.Socket(syscall.AF_INET, syscall.SOCK_STREAM, syscall.IPPROTO_IP)

	if err != nil {
		log.Fatal(err)
	}

	fmt.Println(sock)

}
