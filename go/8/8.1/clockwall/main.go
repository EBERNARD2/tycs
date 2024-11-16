package main

import (
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

func handleConn(c io.Reader, loc string) {
	if _, err := io.Copy(os.Stdout, c); err != nil {
		log.Fatal(err)
	}
}
