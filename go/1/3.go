package main

import (
	"fmt"
	"os"
	"time"
	"strings"
)

func main() {
	start := time.Now()
	s, sep := "", ""
	
	for _, arg := range os.Args[1:] {
		s += sep + arg
	}

	end := time.Now()
	elapsed := end.Sub(start)
	fmt.Println("For loop execution time", elapsed)

	start = time.Now()
	
	strings.Join(os.Args[1:], " ")

	end = time.Now()
	elapsed = end.Sub(start)

	fmt.Println("Joins execution time", elapsed)

}