package main

// This is a static server to fetch static files on FS and return them to proxy server
import (
	"log"
	"net/http"
)

func main() {
	fs := http.FileServer(http.Dir("./static"))
	http.Handle("/", fs)

	log.Print("Listening on port 3005....")

	err := http.ListenAndServe(":3005", nil)

	if err != nil {
		log.Fatal(err)
	}

}
