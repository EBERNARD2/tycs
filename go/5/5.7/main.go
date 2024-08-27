package main


import (
	"fmt"
	"os"
	"net/http"
	"golang.org/x/net/html"
)






var depth int

func main() {
	for _, url := range os.Args[1:] {
		outline(url)
	}
}


func outline(url string) error {
	resp, err := http.Get(url)
	if err != nil {
		return err
	}

	defer resp.Body.Close()

	doc, err := html.Parse(resp.Body)
	if err != nil {
		return err
	}

	forEachNode(doc, startElement, endElement)

	return nil
}

func forEachNode(n *html.Node, pre, post func(n *html.Node)) {
	if pre != nil && n.FirstChild != nil{
		pre(n)
	}

	if n.FirstChild == nil {
		shorthandElement(n)
	}

	for c := n.FirstChild; c != nil; c = c.NextSibling {
		forEachNode(c, pre, post)
	}
	
	if post != nil && n.FirstChild != nil {
		post(n)
	}
}

func shorthandElement(n *html.Node) {
	if n.Type == html.ElementNode {
		s := getAttr(n)
		fmt.Printf("%*s<%s %s/>\n", depth*2, "", n.Data, s)
	}
}

func startElement(n *html.Node) {
	if n.Type == html.ElementNode {
		s := getAttr(n)
		
		fmt.Printf("%*s<%s %s>\n", depth*2, "", n.Data, s)
		depth++
	}
}

func endElement(n *html.Node) {
	if n.Type == html.ElementNode {
		depth--
		fmt.Printf("%*s</%s>\n", depth*2, "", n.Data)
		depth++
	}
}


func getAttr(n *html.Node) string{
	s := ""
	for _, a := range n.Attr {
		s += fmt.Sprintf(" %s=%s", a.Key, a.Val)
	}

	return s
}
