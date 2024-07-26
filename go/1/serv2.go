package main

import (
	"fmt"
	"log"
	"net/http"
	"sync"
)

var mu sync.Mutex
var count int

func main() {
	http.HandleFunc("/", handler)
	http.HandleFunc("/count", counter)
	log.Fatal(http.ListenAndServe("localhost:8000", nil))
}

func handler(w http.ResponseWriter, r *http.Request) {
	fmt.Println(r.URL.Query())
	t := r.URL.Query()
	v := t["count"]
	fmt.Println(v[0])
	mu.Lock()
	count++
	mu.Unlock()
	fmt.Fprintf(w, "URL.Path = %q\n", r.URL.Path)
}

func counter(w http.ResponseWriter, r * http.Request) {
	fmt.Println(r.URL.Query())

	mu.Lock()
	fmt.Fprintf(w, "Count %d\n", count)
	mu.Unlock()
}