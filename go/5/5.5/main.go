package main

import (
	"fmt"
	"os"
	"golang.org/x/net/html"
	"net/http"
	"strings"
)


func main() {
	w, i, _ := CountWordsAndImages(os.Args[1])
	fmt.Printf("Words: %d\t\t Images: %d\n", w, i)
}

func CountWordsAndImages(url string) (words, images int, err error) {
	resp, err := http.Get(url)
	if err != nil {
		return 
	}

	doc, err := html.Parse(resp.Body)
	
	resp.Body.Close()
	if err != nil {
		err = fmt.Errorf("parsing HTML: %s", err)
		return
	}

	words, images = countWordsAndImages(doc)
	return
}


func countWordsAndImages(doc *html.Node) (words, images int) {
	return visit(doc, 0, 0)
}

func visit(n *html.Node, w, i int) (words, images int) {
	words, images = w, i 

	if n == nil {
		return 
	}

	// Get text tags
	if n.Type == html.TextNode && n.Data != "script" && n.Data != "style" {
		d := strings.TrimSpace(n.Data)

		for range strings.Split(d, " ") {
			words++
		}
	}

	if n.Data == "img" {
		images++
	}

	words, images = visit(n.FirstChild, words, images)

	words, images = visit(n.NextSibling, words, images) 

	return 
}