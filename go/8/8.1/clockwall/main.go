package main

import (
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

	}
}

func writeConn(c *net.Conn, loc string) {

}
