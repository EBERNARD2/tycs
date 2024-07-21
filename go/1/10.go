package main 

import (
	"fmt"
	"io"
	"io/ioutil"
	"net/http"
	"os"
	"time"
)

func main() {
	start := time.Now()
	ch := make(chan string)
	for _, url := range os.Args[1:] {
		go fetch(url, ch)
	}

	for range os.Args[1:] {
		fmt.Println(<-ch)
	}

	fmt.Printf("%.2fs elapsed", time.Since(start).Seconds())
}


func fetch(url string, ch chan<- string) {
	start := time.Now()
	resp, err := http.Get(url)

	if err != nil {
		ch <- fmt.Sprint(err)
		return 
	}
	nbytes, err := io.Copy(ioutil.Discard, resp.Body)

	filename := url + ".txt"
	f, err := os.Create(filename)
	fmt.Println(filename)
	if err != nil {
		ch <- fmt.Sprintf("while creating file %s: %v", url, err)
		return 
	}

	if _, err := io.Copy(f, resp.Body); err != nil {
		ch <- fmt.Sprintf("while writing to file %s: %v", filename, err)
		return
	}

	resp.Body.Close()
	if err != nil {
		ch <- fmt.Sprintf("while reading %s: %v", url, err)
		return
	}

	secs := time.Since(start).Seconds()
	ch <- fmt.Sprintf("%.2fs %7d %s", secs, nbytes, url)
}