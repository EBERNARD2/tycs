package main

import (
	"fmt"
	"os"
	"golang.org/x/net/html"
)

func main() {
	doc, err := html.Parse(os.Stdin)
	if err != nil {
		fmt.Fprintf(os.Stderr, "findlinks1: %v\n", err)
		os.Exit(1)
	}


	elementCount := make(map[string]int)
	visit(elementCount, doc)

	fmt.Println(elementCount)

}


func visit(elementCount map[string]int, n *html.Node) map[string]int {
	if n == nil {
		return elementCount
	}

	// Process all link tags in current html element
	if n.Type == html.ElementNode {
		elementCount[n.Data]++
	}

	elementCount = visit(elementCount, n.FirstChild)

	elementCount = visit(elementCount, n.NextSibling) 

	return elementCount
}