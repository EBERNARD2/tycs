package main

import (
	"fmt"
	"os"
	"strings"
)

func main() {
	fmt.Println(len(os.Args))
	if len(os.Args) == 1 {
		fmt.Printf("Usage: xkcd.go {search term}")
		os.Exit(1)
	}

	str := strings.Join(os.Args[1:], " ")
	
}
