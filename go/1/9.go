package main 

import (
	"fmt"
	"io"
	"net/http"
	"os"
	"strings"
)

func main() {
	for _, input := range os.Args[1:] {
		url := input
		if !strings.HasPrefix(url, "http://") {
			url = "http://" + url
		}

		resp, err := http.Get(url)
		if err != nil {
			fmt.Fprintf(os.Stderr, "fetch: %v with status code: %s\n", err, resp.Status)
			os.Exit(1)
		}

		fmt.Printf("Response status code for %s was %s\n", url, resp.Status)

		if _, err := io.Copy(os.Stdout, resp.Body); err != nil {
			fmt.Fprintf(os.Stderr, "fetch: reading : %s %v", url, err)
			os.Exit(1)
		}
	}
}