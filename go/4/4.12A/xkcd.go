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
	unmarshalData()

}


func unmarshalData() {
	// get data from file
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

	fmt.Println(data)

}