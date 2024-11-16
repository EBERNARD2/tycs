package main

import (
	"fmt"
	"io"
	"log"
	"net"
	"os"
	"strings"
)

// We are going to skip validation
func main() {

	for _, arg := range os.Args[1:] {
		values := strings.Split(arg, "=")
		if len(values) != 2 {
			log.Fatalf("Usage: ./{program name} {Location}=localhost:{PORT}")
		}

		if !strings.HasPrefix(values[1], "localhost:") {
			log.Fatalf("Usage: ./{program name} {Location}=localhost:{PORT}")
		}

		conn, err := net.Dial("tcp", values[1]) // create a new connection
		if err != nil {
			log.Fatal(err)
		}

		defer conn.Close()

		go handleConn(conn, values[0])
	}
}

func handleConn(c net.Conn, loc string) {

	// read from connection

	for {
		buff := make([]byte, 1024)
		n, err := c.Read(buff)
		if err != nil {
			if err == io.EOF {
				break
			} else {
				log.Printf("Error reading: %v \n", err)
				break
			}
		}
		fmt.Printf("Time in %s: %s \n", loc, string(buff[:n]))

	}
}
