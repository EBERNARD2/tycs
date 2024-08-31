package main


import (
	"fmt"
	"os"
	"net/http"
	"golang.org/x/net/html"
	"log"
)



func main() {
	if len(os.Args[1:]) != 2 {
		log.Fatalf("Usage: go run {filename} {url} {element id}\n")
		os.Exit(1)
	}

	doc, err := getDoc(os.Args[1])

	if err != nil {
		log.Fatalf("Error could not get document from url: %v\n", err)
		os.Exit(1)
	}
	
	ele := ElementByID(doc, os.Args[2])

	if ele == nil {
		fmt.Printf("Element by id: %v not found.. Please try again\n", os.Args[2])
	} else {
		fmt.Printf("Node Found: \n\n%v\n", ele)
	}
	
}


func getDoc(url string) (*html.Node, error) {
	resp, err := http.Get(url)
	if err != nil {
		return nil, err
	}

	defer resp.Body.Close()

	doc, err := html.Parse(resp.Body)
	if err != nil {
		return nil, err
	} 
	return doc, err
}



func ElementByID(n *html.Node, id string) *html.Node {
	return forEachNode(n, id, foundIdElement, foundIdElement)
}

func forEachNode(n *html.Node, query string, pre, post func(n *html.Node, query string)) *html.Node {
	if pre != nil && pre(n, query){
		return n
	}

	for c := n.FirstChild; c != nil; c = c.NextSibling {
		node := forEachNode(c, query, pre, post)

		if node != nil {
			return node
		}
	}
	
	if post != nil && post(n, query)  {
		return n
	}

	return nil
}


func foundIdElement(n *html.Node, idQuery string) bool {
	if n.Type == html.ElementNode {
		for _, a := range n.Attr {
			if a.Key == "id" && a.Val == idQuery {
				return true
			}
		}
	}
	return false
}
