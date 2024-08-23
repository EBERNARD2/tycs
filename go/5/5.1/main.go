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

	for _, link := range visit(nil, doc){
		fmt.Println(link)
	}

	fmt.Println(doc.Data)
}


func visit (links []string, n *html.Node) []string {
	// Base Case
	if n == nil {
		return links
	}

	// Process all link tags in current html element
	if n.Type == html.ElementNode && n.Data == "a" {
		for _, a := range n.Attr {
			if a.Key == "href" {
				links = append(links, a.Val)
			}
		}
	}

	links = visit(links, n.FirstChild)

	links = visit(links, n.NextSibling) 

	return links
}