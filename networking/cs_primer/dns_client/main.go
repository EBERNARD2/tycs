package main

import (
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
	Header format:

		2 bytes per row

		1st row - Identification --- Will probably be 0x0000 as this query is our first
			ID - 2 bytes

		2nd row:

			1 bit will be 0 to reprensent that this is a query
			next 4 bits will be 0x0 to represnet a standard query
			1 bit is 0 as Authoratative answer is only valid in responses
			1 bit is 0 for truncation... will assume we will have enought bytes
			1 bit will be 0 for Recursion desired
			1 bit will be 0 for Recursion available
			Z bit (1 bit) is reserved for future use
			4 bits are the Response code and are 0

		3rd row:
			2 bytes specifiying the number of entries in the question section - this will be based on the number
			of arguments from cli

		4th row:
			2 bytes that will be 0x0000 as this is for the answer section( we need to parse this area of the response though)

			5th and 6th row:

				these will be like row 4: 0x0000 for our query... (plus we won't need to parse). These represent
				Name server and additional resource section which are outside of the scope of this project


		The next most important piece will be the Question field of the qeury. We will need to build one of these (in bytes)
		for each domain provided on the command line

		each question query will be 12 bytes so we need to account that a udp packet can only contain 512 bytes

		row 1:
			2 bytes for the name... This will be provided by command line args

		row 2:
			2 bytes for the type. We are looking for the ip address for those domain aliases so we'll query A records

		row 3:
			2 bytes for class... This is simple.. We want to use the internet so pass 0x0001

		row 4:
			2 bytes for TTL.. We can just use 0x0400 (1024 seconds or about 18 mins)

		row 5:
			2 bytes for length of the variable length data being requested.

		row 6 and on...:

			convert

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

	fmt.Println(res[3] & 0xF) // check Rcode

	if res[3]&0xf != 0 {
		log.Fatal("Error fetching Domain ip address.. Please try again")
	}

	// Skip the query section of the response
	i := 12
	for ; res[i] != 0; i++ {
	}

	i = i + 5

	fmt.Printf("Ip address(es) for domain: %s\n\n", os.Args[1])
	// Answer section (Stop 10 bytes before reaching max of 512):
	for ; i < 502; i += 16 {
		//2 bytes for compressed / hashed resource name
		// 2 bytes for type
		// 2 bytes for class
		// 2 bytes for TTL
		// 2 bytes for Data length - Will always be 4 bytes for A records
		if res[i+11] == 0x04 {
			fmt.Printf("%d.%d.%d.%d\n", uint8(res[i+12]), uint8(res[i+13]), uint8(res[i+14]), uint8(res[i+15]))
		}
	}
}
