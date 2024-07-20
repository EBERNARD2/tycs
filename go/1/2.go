package main

import (
	"fmt"
	"os"
)

func main() {
	s, sep := "", ""

	for idx, arg := range os.Args[1:] {
		fmt.Println(idx, arg)
		s += sep + arg
		sep = " "
	}

	fmt.Println(s, "final string")
}