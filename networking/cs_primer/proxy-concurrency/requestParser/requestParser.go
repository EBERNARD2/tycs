package main

import (
	"bytes"
	"fmt"
	"log"
	"slices"
	"strings"
)

var ACCEPTED_METHODS = []string{"GET", "PUT", "PATCH", "DELETE"}
var ACCEPTED_VERSIONS = []string{"HTTP/1.0", "HTTP/1.1", "HTTP/2"}

type HTTPMessage struct {
	Method  string
	Version string
	Uri     string
	Headers map[string]string
	Body    []byte
}

func Parser(b []byte) (*HTTPMessage, error) {
	parseRequest := bytes.Split(b, []byte{0x0d, 0x0a})
	var message HTTPMessage

	requestLine := bytes.Split(parseRequest[0], []byte{32})

	message.Method = string(requestLine[0])
	message.Uri = string(requestLine[1])
	message.Version = string(requestLine[2])

	if !slices.Contains(ACCEPTED_METHODS, message.Method) {
		return nil, fmt.Errorf("Method not accepted: %s", message.Method)
	}

	if !slices.Contains(ACCEPTED_VERSIONS, message.Version) {
		return nil, fmt.Errorf("Version not accepted: %s", message.Version)
	}

	// make headers
	message.Headers = make(map[string]string)

	for i := 1; i < len(parseRequest); i++ {
		header := strings.Split(string(parseRequest[i]), ": ")

		if len(header) < 2 {
			continue
		}
		message.Headers[header[0]] = header[1]
	}

	fmt.Println(message.Headers)

	return &message, nil

}

func main() {
	req, err := Parser([]byte("GET / HTTP/1.0\r\nHOST: google.come\r\nConnection: keep-alive\r\n\r\n"))

	if err != nil {
		log.Fatal(err)
	}

	fmt.Println(req.Headers["Connection"])
}
