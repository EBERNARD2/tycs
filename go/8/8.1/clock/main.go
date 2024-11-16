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

	var location *time.Location
	sendWithLocation := false

	if timeZone != "" {
		val, err := time.LoadLocation(timeZone)

		if err != nil {
			log.Printf("Error processing %s timezone: %v", timeZone, err)
			return // close connection if timezone wrong
		}

		location = val
		sendWithLocation = true
	}

	for {
		var timeString string

		if sendWithLocation {
			timeString = time.Now().In(location).Format("15:04:05\n")
		} else {
			timeString = time.Now().Format("15:04:05\n")
		}

		_, err := io.WriteString(c, timeString) // write string to connection

		if err != nil {
			return
		}

		time.Sleep(1 * time.Second)
	}
}
