package main

import (
	"fmt"
	"os"
	"golang.org/x/net/html"
	"strings"
)

func main() {
	doc, err := html.Parse(os.Stdin)
	if err != nil {
		fmt.Fprintf(os.Stderr, "findlinks1: %v\n", err)
		os.Exit(1)
	}

	visit(doc)

}


func visit(n *html.Node) {
	if n == nil {
		return 
	}

	// Process all link tags in current html element
	if n.Type == html.TextNode && n.Data != "script" && n.Data != "style" {
		d := strings.TrimSpace(n.Data)

		if d != "" {
			fmt.Println(d)
		}

		// for _, a := range n.Attr {
		// 	fmt.Println(a)
		// }
	}

	visit(n.FirstChild)

	visit(n.NextSibling) 
}