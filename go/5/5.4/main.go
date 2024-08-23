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

	for _, source := range visit(nil, doc){
		fmt.Println(source)
	}

	fmt.Println(doc.Data)
}


func visit (source []string, n *html.Node) []string {
	// Base Case
	if n == nil {
		return source
	}

	// Process all link tags in current html element
	if n.Type == html.ElementNode && n.Data == "a" {
		for _, a := range n.Attr {
			if a.Key == "href" {
				source = append(source, a.Val)
			}
		}
	}

	if n.Type == html.ElementNode && n.Data == "img" {
		for _, a := range n.Attr {
			if a.Key == "src" {
				source = append(source, a.Val)
			}
		}
	}

	if n.Type == html.ElementNode && n.Data == "script" {
		for _, a := range n.Attr {
			if a.Key == "src" {
				source = append(source, a.Val)
			}
		}
	}

	if n.Type == html.ElementNode && n.Data == "stylesheet" {
		for _, a := range n.Attr {
			if a.Key == "src" {
				source = append(source, a.Val)
			}
		}
	}

	source = visit(source, n.FirstChild)

	source = visit(source, n.NextSibling) 

	return source
}