package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	seen := make(map[string]int)
	input := bufio.NewScanner(os.Stdin)

	input.Split(bufio.ScanWords)

	for input.Scan() {
		word := input.Text()

		seen[word]++
	}

	if err := input.Err(); err != nil {
		fmt.Fprintf(os.Stderr, "wordfreq %v\n", err)
		os.Exit(1)
	}

	printCounts(seen)
}

func printCounts(counts map[string]int) {
	for k, v := range counts {
		fmt.Printf("%s occurrences: %d\n", k, v)
	}
}