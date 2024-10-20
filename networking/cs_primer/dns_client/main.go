package main

import (
	"bytes"
	"fmt"
	"log"
	"os"
	"strings"
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
	resolverAddr = [4]byte{1, 1, 1, 1} // This is the address for cloudflare's public dns resolver
)

// Get CLI Arguments
func main() {
	readClArgs()
	// Create UDP socket to query DNS resolver
	// sock, err := syscall.Socket(syscall.AF_INET, syscall.SOCK_DGRAM, syscall.IPPROTO_IP)

	// if err != nil {
	// 	log.Fatalf("Error creating socket... Please run client again\n")
	// }

	dnsQuery := createQueryHeader()

	for _, domain := range os.Args[1:] {
		dnsQuery = append(dnsQuery, createQuestion(domain)...)
	}

	fmt.Println(dnsQuery)
	// Query DNS resolver (HOW?)

	// Parse the response

}

func readClArgs() {
	if len(os.Args[1:]) == 0 {
		log.Fatalf("Usage: file-name {domain name}\n")
	}

	arg := os.Args[1]

	// maybe add some validation here to make sure its what a DNS server expects

	fmt.Printf("This is a valid argument: %s\n", arg)
}

func createQueryHeader() []byte {
	var header bytes.Buffer

	// Row 1
	// header.Write([]byte{0x})
	header.WriteByte(0x00)
	header.WriteByte(0x00)

	// Row 2 write bytes for QR|  Opcode  |AA|TC|RD|RA |  Z    |   RCODE
	header.WriteByte(0x01)
	header.WriteByte(0x00)

	// Row 3 get number of queries we'll have
	count := len(os.Args[1:])

	header.WriteByte(byte(count & 0xFF00))
	header.WriteByte(byte(count & 0x00FF))

	// Row 3
	header.WriteByte(0x00)
	header.WriteByte(0x00)
	// Row 4
	header.WriteByte(0x00)
	header.WriteByte(0x00)
	// Row 5
	header.WriteByte(0x00)
	header.WriteByte(0x00)

	return header.Bytes()
}

func createQuestion(domain string) []byte {
	var question bytes.Buffer

	for _, segment := range strings.Split(domain, ".") {
		question.WriteByte(byte(len(segment))) // write length
		question.WriteString(segment)          // write domain segment
	}

	question.WriteByte(0x00)       // Terminate domain query
	question.Write([]byte{0x0001}) // Add Type - A record
	question.Write([]byte{0x0001}) // Class - the internet

	return question.Bytes()
}
