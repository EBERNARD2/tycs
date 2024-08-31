package main

import (
	"fmt"
	"log"
	"os"
)

func main() {
	breadthFirst(crawl, os.Args[1:])
}

func breadthFirst(f func(item string) []string, worklist string) {
	seen := make(map[string]bool)
	for len(worklist) > 0 {
		worklist = nil
		for _, item := range items {
			if  !seen[item] {
				seen[item] = true
				worklist = append(worklist, f(item)...)
			}
		}
	}
}

func crawl(url string) []string {
	fmt.Println(url)
	list, err := links.Extract(url)
	if err != nil {
		log.Print(err)
	}
	return list
}