package main

import (
	"fmt"
	"os"
	"strings"
	"io"
	"log"
	"encoding/json"
)

type ComicData struct {
	Month 	   string `json:"month"`
	Num 		   int		`json:"num"`
	Year		   string	`json:"year"`
	News 		   string `json:"news"`
	SafeTitle  string `json:"safe_title"`
	Transcript string `json:"transcript"`
	Alt 			 string `json:"alt"`
	Img				 string `json:"img"`
	Title 		 string `json:"title"`
	Day 			 string `json:"day"`
	Url 			 string 
}

type Comics struct {
	ComicIndex map[int]ComicData
	TranscriptIndexes map[string]int
}


func main() {
	fmt.Println(len(os.Args))
	if len(os.Args) == 1 {
		fmt.Printf("Usage: xkcd.go {search term}")
		os.Exit(1)
	}

	str := strings.Join(os.Args[1:], " ")
	fmt.Println(str)
	
	data := unmarshalData()
	searchAndPrint(strings.Join(os.Args[1:], " "), data)
}


func unmarshalData() *Comics{
	file, err := os.Open("index.txt")

	if err != nil {
		log.Fatalf("Failed to open file: %s", err)
	}

	b, err := io.ReadAll(file)
	
	if err != nil {
		log.Fatalf("Reading file failed: %s", err)
		os.Exit(1)
	}

	var data Comics 

	if err := json.Unmarshal(b, &data); err != nil {
		log.Fatalf("JSON unmarshalling failed: %s", err)
	}

	return &data
}


func searchAndPrint(query string, data *Comics) {
	var foundComics []ComicData

	for tString, index := range data.TranscriptIndexes {
		if strings.Contains(tString, query) {
			foundComics = append(foundComics, data.ComicIndex[index])
		}
	}

	if len(foundComics) == 0 {
		fmt.Printf("No results found for query: %s\n", query)
	} else {

		fmt.Printf("COMICS FOUND %d\n\nComic URL \t\t\tTranscript\n\n", len(foundComics))
	}

	for _,c := range foundComics {
		fmt.Printf("%s\t\t%s\n\n", c.Url, c.Transcript)
	}	
}