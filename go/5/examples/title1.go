package title

import (
	"net/http"
	"strings"
	"fmt"
	"golang.org/x/net/html"
)

func title(url string) error {
	resp, err := http.Get(url)
	if err != nil {
		return err
	}

	ct := resp.Header.Get("Content-Type")
	if ct != "text/html" && !strings.HasPrefix(ct, "text/html") {
		resp.Body.Close()
		return fmt.Errorf("%s has type, not text/html", url, ct)
	}

	doc, err := html.Parse(resp.Body)
	resp.Body.Close()
	if err != nil {
		return fmt.Errorf("parsing %s HTML %v", url, err)
	}

	visitNode := func(n *html.Node) {
		if n.Type == html.ElementNode && n.Data == "title" && 
			n.FirstChild != nil {
				fmt.Println(n.FirstChild.Data)
			}
	}
=