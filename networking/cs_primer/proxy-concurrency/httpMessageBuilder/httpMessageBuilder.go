package httpMessageBuilder

import (
	"bytes"
	"fmt"
	"slices"
	"strings"
)

var acceptedMethods = []string{"GET", "POST", "PATCH", "DELETE"}
var acceptedVersions = []string{"HTTP/1.0", "HTTP/1.1", "HTTP/2"}

type HTTPMessage struct {
	Method  string
	Version string
	Uri     string
	Headers map[string]string
	Body    []byte
}

func BuildMessage(b []byte) (*HTTPMessage, error) {
	bodyStartIndex := bytes.Index(b, []byte{0x0d, 0x0a, 0x0d, 0x0a})
	parseRequest := bytes.Split(b[:bodyStartIndex], []byte{0x0d, 0x0a})
	var message HTTPMessage

	requestLine := bytes.Split(parseRequest[0], []byte{32})

	message.Method = string(requestLine[0])
	message.Uri = string(requestLine[1])
	message.Version = string(requestLine[2])

	if !slices.Contains(acceptedMethods, message.Method) {
		return nil, fmt.Errorf("Method not accepted: %s", message.Method)
	}

	if !slices.Contains(acceptedVersions, message.Version) {
		return nil, fmt.Errorf("Version not accepted: %s", message.Version)
	}

	// make headers
	message.Headers = make(map[string]string)

	for i := 1; i < len(parseRequest); i++ {
		header := strings.Split(string(parseRequest[i]), ": ")
		message.Headers[header[0]] = header[1]
	}

	// add body to http message body.. Skip CRLF
	message.Body = b[bodyStartIndex+4:]

	return &message, nil

}
