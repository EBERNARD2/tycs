package main

import (
	"bytes"
	"fmt"
	"log"
	"os"
	"slices"
	"strings"
	"syscall"
)

var (
	ADDR          = []byte{127, 0, 0, 1}
	OWN_PORT      = 8080
	UPSTREAM_PORT = 3005
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

func logger(err error, fatal bool) {
	if fatal && err != nil {
		log.Fatal(err)
		os.Exit(1)
	} else if err != nil {
		log.Print(err)
	}
}

func main() {
	sock := createSocket()
	defer syscall.Close(sock)
	bindAndListen(sock)

	for {
		clientSock, clientAddr, err := syscall.Accept(sock)
		if err != nil {
			log.Printf("Error establishing connection with client: %v", err)
			continue
		}
		fmt.Printf("New Connection from %v\n", clientAddr)

		go clientConnection(clientSock)

	}
}

func clientConnection(clientSock int) {
	upstreamAddr := syscall.SockaddrInet4{Port: UPSTREAM_PORT, Addr: [4]byte(ADDR)}

	for {
		var msg = make([]byte, 4096)
		n, err := syscall.Read(clientSock, msg)

		if n == 0 {
			continue
		}

		if err != nil {
			log.Printf("Error reading from client socket: %v", err)
			continue
		}

		req, err := BuildMessage(msg[:n])

		if err != nil {
			log.Printf("Error building http message: %v", err)
			continue
		}

		go connectClientUpstream(clientSock, msg[:n], upstreamAddr)

		// if connection is keep alive continue else close connection
		if req.Headers["Connection"] == "keep-alive" {
			continue
		}

		// if the connection is not keep alive then break out of loop
		break
	}

	// close client socket
	err := syscall.Close(clientSock)
	if err != nil {
		log.Printf("Error closing client socket: %v\n", err)
		return
	}

}

func connectClientUpstream(clientSock int, msg []byte, upstreamAddr syscall.SockaddrInet4) {
	upstreamSocket, err := syscall.Socket(syscall.AF_INET, syscall.SOCK_STREAM, syscall.IPPROTO_IP)

	if err != nil {
		log.Printf("Error creating upstream socket: %v\n", err)
		return
	}

	err = syscall.Connect(upstreamSocket, &upstreamAddr)
	if err != nil {
		log.Printf("Failure connectiing to port upstream\n")
		return
	}

	n, err := syscall.Write(upstreamSocket, msg)

	fmt.Printf("Wrote %d bytes to upstream\n", n)

	if err != nil {
		log.Printf("Error sending upstream: %v\n", err)
		return
	}

	for {
		var res = make([]byte, 4096)

		n, err := syscall.Read(upstreamSocket, res)

		if n == 0 {
			break
		}

		if err != nil {
			log.Printf("Failure reading from upstream server: %v\n", err)
			continue
		}

		fmt.Printf("Read %d bytes\n", n)

		n, err = syscall.Write(clientSock, res[:n])
		if err != nil {
			log.Printf("Failure writing to client: %v\n", err)
			continue
		}

		fmt.Printf("Wrote %d bytes\n", n)
	}

	err = syscall.Close(upstreamSocket)
	if err != nil {
		log.Printf("Error closing upstream socket: %v\n", err)
		return
	}

	fmt.Println("Closed upstrean socket")
}

func bindAndListen(sock int) {
	proxyAddr := syscall.SockaddrInet4{Port: OWN_PORT, Addr: [4]byte(ADDR)}

	logger(syscall.Bind(sock, &proxyAddr), true)

	logger(syscall.Listen(sock, 50), true)

	fmt.Printf("Server listening on port %d...\n", proxyAddr.Port)
}

func createSocket() int {
	sock, err := syscall.Socket(syscall.AF_INET, syscall.SOCK_STREAM, syscall.IPPROTO_IP)
	logger(syscall.SetsockoptInt(sock, syscall.SOL_SOCKET, syscall.SO_REUSEADDR, 1), true)
	logger(syscall.SetNonblock(sock, true), true)

	logger(err, true)

	return sock
}

func BuildMessage(b []byte) (*HTTPMessage, error) {
	bodyStartIndex := bytes.Index(b, []byte{0x0d, 0x0a, 0x0d, 0x0a})

	if bodyStartIndex == -1 {
		return nil, fmt.Errorf("message not properly formated")
	}

	parseRequest := bytes.Split(b[:bodyStartIndex], []byte{0x0d, 0x0a})
	var message HTTPMessage

	requestLine := bytes.Split(parseRequest[0], []byte{32})

	message.Method = string(requestLine[0])
	message.Uri = string(requestLine[1])
	message.Version = string(requestLine[2])

	if !slices.Contains(acceptedMethods, message.Method) {
		return nil, fmt.Errorf("method not accepted: %s", message.Method)
	}

	if !slices.Contains(acceptedVersions, message.Version) {
		return nil, fmt.Errorf("version not accepted: %s", message.Version)
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
