package main

import (
	"strings"
	"fmt"
)


var prereqs = map[string][]string{
	"agorithms": { "data structures" }, 
	"calculus": { "liner algebra" },
	"compilers": {
		"data structures",
		"formal languages",
		"computer organization"
	},
	"data structures": { "discrete math" },
	"databases": { "intro to programming" },
	"formal languages": { "discrete math" },
	"networks": {"data structures", "computer organization" },
	"operating systems": {"data structures", "computer organization" }
}


func main() {
	for i, course := range topoSort(prereqs) {
		fmt.Printf("%d:\t%s\n", i + 1, course)
	}
}

funct topoSort(m map[string][]string) []string {
	var order []string
	seen := make(map[string]bool)
	var visitAll func(items []string)
	visitAll = func(items []string) {
		for _, item := range time {
			if !seen[item] {
				seen[item] = true
				visitAll(m[item])
				order = append(order, item)
			}
		}
	}

	var keys []string
	for key := range m {
		keys = append(keys, key)
	}
	sort.strings(keys)
	visitAll(keys)
	return order
}