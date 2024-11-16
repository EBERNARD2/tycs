package main

import (
	"flag"
	"fmt"
	"io"
	"log"
	"net"
	"os"
	"time"
)

func main() {

	portPtr := flag.String("port", "8000", "localhost port")

	flag.Parse()

	listner, err := net.Listen("tcp", fmt.Sprintf("localhost:%s", *portPtr))

	if err != nil {
		log.Fatal(err)
	}

	for {
		conn, err := listner.Accept()
		if err != nil {
			log.Print(err) // connection aborted
			continue
		}

		go handleConn(conn)
	}
}

func handleConn(c net.Conn) {
	defer c.Close()

	// get timezone
	timeZone := os.Getenv("TZ")

	var timeString string

	if timeZone == "" {
		// machine location will be default timezone
		timeString = time.Now().Format("15:04:05\n")

	} else {

		// get the tim
		loc, err := time.LoadLocation(timeZone)
		if err != nil {
			log.Printf("Error processing %s timezone: %v", timeZone, err)
			return // close connection if timezone wrong
		}

		timeString = time.Now().In(loc).Format("15:04:05\n")
	}

	for {
		_, err := io.WriteString(c, timeString) // write string to connection

		if err != nil {
			return
		}
		time.Sleep(1 * time.Second)
	}
}
