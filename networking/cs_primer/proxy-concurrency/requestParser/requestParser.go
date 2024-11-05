package main

import (
	"bytes"
	"fmt"
	"slices"
)

var ACCEPTED_METHODS = []string{"GET", "PUT", "PATCH", "DELETE"}
var ACCEPTED_VERSIONS = []string{"HTTP/1.0", "HTTP/1.1", "HTTP/2"}

type HTTPRequest struct {
	Method  string
	Version string
}

func Parse(b []byte) (*HTTPRequest, error) {
	parseRequest := bytes.Split(b, []byte{0x0d, 0x0a})
	var req HTTPRequest

	requestLine := bytes.Split(parseRequest[0], []byte{32})

	// get
	req.Method = string(requestLine[0])
	req.Version = string(requestLine[2])

	if !slices.Contains(ACCEPTED_METHODS, req.Method) {
		return nil, fmt.Errorf("Method not accepted: %s", req.Method)
	}

	if !slices.Contains(ACCEPTED_VERSIONS, req.Version) {
		return nil, fmt.Errorf("Version not accepted: %s", req.Version)
	}

	fmt.Println("ok")

	for i := 1; i < len(parseRequest); i++ {
		line := parseRequest[i]

		fmt.Println(string(line))
	}

	return &req, nil

}

func main() {
	Parse([]byte("GET / HTTP/1.0\r\nHOST: google.come\r\nConnection: keep-alive\r\n\r\n"))
}
