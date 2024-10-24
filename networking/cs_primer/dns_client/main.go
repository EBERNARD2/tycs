package main

import (
	"bytes"
	"encoding/binary"
	"fmt"
	"log"
	"math/rand"
	"os"
	"strings"
	"syscall"
)

/*
	using RFC 1035 https://www.ietf.org/rfc/rfc1035.txt as a guide to build dns query
*/

var (
	resolverAddr = [4]byte{8, 8, 8, 8} // This is the address for google's public dns resolver
	PORT         = 53                  // This is the DNS PORT
)

// Get CLI Arguments
func main() {
	readClArgs()

	dnsQuery := createQueryHeader()

	for _, domain := range os.Args[1:] {
		dnsQuery = append(dnsQuery, createQuestion(domain)...)
	}

	id := dnsQuery[0:2]
	// Parse the response
	response := sendDnsQuery(dnsQuery)

	parseResponse(response, id)

}

// Query DNS resolver

func sendDnsQuery(dnsQuery []byte) []byte {
	// Create UDP socket to query DNS resolver
	sock, err := syscall.Socket(syscall.AF_INET, syscall.SOCK_DGRAM, syscall.IPPROTO_IP)

	if err != nil {
		log.Fatalf("Error creating socket... Please run client again\n")
	}

	dnsAddr := syscall.SockaddrInet4{Addr: resolverAddr, Port: PORT}

	msg := make([]byte, 512)
	syscall.Sendto(sock, dnsQuery, 0, &dnsAddr)

	_, _, err = syscall.Recvfrom(sock, msg, syscall.MSG_WAITALL)

	if err != nil {
		log.Fatalf("Error recieving DNS message: %v\n", err)
	}

	err = syscall.Close(sock)

	if err != nil {
		log.Fatalf("Error closing sockiet: %s\n", err)
	}

	return msg
}

func readClArgs() {
	if len(os.Args[1:]) == 0 {
		log.Fatalf("Usage: file-name {domain name}\n")
	}

	// maybe add some validation here to make sure its what a DNS server expects
}

func createQueryHeader() []byte {
	head := make([]byte, 12)

	// TODO: Change these bytes to big endian as I forgot Apple machines use little endian.. We need to explicity set these
	// Row 1
	id := rand.Intn(65535)
	binary.BigEndian.PutUint16(head[0:2], uint16(id))

	// Row 2 write bytes for QR|  Opcode  |AA|TC|RD|RA |  Z    |   RCODE
	binary.BigEndian.PutUint16(head[2:4], 0x0100)

	// Row 3 get number of queries we'll have
	binary.BigEndian.PutUint16(head[4:6], uint16(len(os.Args[1:])))

	// Rows 4 5 and 6 are set will be set to 0
	return head
}

func createQuestion(domain string) []byte {

	var question []byte
	for _, segment := range strings.Split(domain, ".") {
		question = append(question, byte(len(segment))) // write length
		question = append(question, []byte(segment)...) // write domain segment
	}

	question = append(question, []byte{0x00, 0x00, 0x01, 0x00, 0x01}...)

	return question
}

// We will need to check the queries section of the response to see if there is
func parseResponse(res []byte, id []byte) {
	//check response header and match with id
	if res[0] != id[0] || res[1] != id[1] {
		log.Fatalf("Request and response ids don't match: %v and %v\n", res[0:2], id)
	}

	// check rcode
	if res[3]&0xf != 0 {
		log.Fatal("Error fetching Domain ip address.. Please try again")
	}

	// Skip the query section of the response
	i := 12
	for ; res[i] != 0; i++ {
	}

	i = i + 5

	fmt.Printf("Relevant Ip address for %s:\n", os.Args[1])
	//2 bytes for compressed / hashed resource name
	// 2 bytes for type
	// 2 bytes for class
	// 2 bytes for TTL
	// 2 bytes for Data length - Will always be 4 bytes for A records
	for _, answer := range bytes.Split(res[i:], []byte{192}) {

		if len(answer) < 15 {
			continue
		}

		if answer[1] == 0x0 && answer[2] == 0x1 {

			fmt.Printf("%d.%d.%d.%d\n", answer[11], answer[12], answer[13], answer[14])
		}

	}
}
