package main

import (
	"fmt"
	"os"
	"bufio"
)

func main() {
	counts := make(map[string]int)
	files := os.Args[1:]

	if len(files) == 0 {
		countlines(os.Stdin, counts)
	} else {
		for _, arg := range files {
			f, err := os.Open(arg)

			if err != nil {
				fmt.Fprintf(os.Stderr, "dup2 %v\n", err)
				continue
			}

			countlines(f, counts)
			f.Close()
		}
	}
	for line, n := range counts {
		if n > 1 {
			fmt.Printf("%d\t\t%s\n", n, line)
		}
	}
}

func countlines(f *os.File, counts map[string]int) {
	input := bufio.NewScanner(f)
	for input.Scan() {
		counts[input.Text()]++
	}
}