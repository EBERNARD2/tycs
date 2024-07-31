package main

import (
	"fmt"
	"os"
	"crypto/sha256"
	"crypto/sha512"
)


func main() {
	args := os.Args[1:]

	if len(args) == 0 {
		printShaHash("SHA256")
		
	} else if len(args) == 1 {
		flag := args[0]

		if flag == "-SHA384" {
			printShaHash(flag[:1])

		} else if flag == "-SHA512" {
			printShaHash(flag[1:])

		} else {
			printErr("Error: incorrect flag\nUsage: filename -SHA384 OR filename -SHA512\n")
		}

	} else {
		// too many arguments error
		printErr("Error: too many command line arguments\nUsage: filename -flag\n")
	}
}

func printErr(msg string) {
	fmt.Fprintf(os.Stderr, msg)
}

func printShaHash(hash string) {

	if hash == "SHA256" {
		fmt.Printf("%X\n", sha256.Sum256([]byte("x")))
	}

	if hash == "SHA384" {
		fmt.Printf("%X\n", sha512.Sum384([]byte("x")))
	}

	if hash == "SHA512" {
		fmt.Printf("%X\n", sha512.Sum512([]byte("x")))
	}
}
