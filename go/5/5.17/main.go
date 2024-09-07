package main

import (
	"fmt"
	"os"
	"golang.org/x/net/html"
)


func main() {
	doc, err := html.Parse(os.Stdin)

	if err != nil {
		fmt.Fprintf(os.Stderr, "elements by tag name: %v\n", err)
		os.Exit(1)
	}


	PrintNodes(ElementsByTagName(doc, "img"))
	PrintNodes(ElementsByTagName(doc, "h1", "h2", "h2", "h3"))

}

func ElementsByTagName(doc *html.Node, name ...string) []*html.Node {
	var nodes []*html.Node

	if len(name) == 0 {
		return nodes
	}

	for _, v := range name {
		tagVals := visit(nil, doc, v)
		nodes = append(nodes, tagVals...)
	}

	return nodes
}

func visit (nodes []*html.Node, n *html.Node , tag string) []*html.Node {
	if n == nil {
		return nodes
	}

	// Process all link tags in current html element
	if n.Type == html.ElementNode && n.Data == tag {
		nodes = append(nodes, n)
	}

	nodes = visit(nodes, n.FirstChild, tag)

	nodes = visit(nodes, n.NextSibling, tag) 

	return nodes
}

func PrintNodes(nodes []*html.Node) {
	for _, v := range nodes {
		fmt.Println(v)
	}
}

