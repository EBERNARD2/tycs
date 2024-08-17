package main


import (
	"fmt"
	"net/http"
	"log"
	"encoding/json"
	"os"
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


const BaseUrl = "https://xkcd.com/info.0.json"

func main() {

	// fetch current number of comics 
	currentNumOfComics := runSetup()
	buildIndex(currentNumOfComics)

	// for every request, create a comic
}


func runSetup() int {
	// fetch current number of comics 
	resp, err := http.Get(BaseUrl)

	if err != nil {
		log.Fatal(err)
		os.Exit(1)
	}

	if resp.StatusCode != http.StatusOK {
		resp.Body.Close()
		fmt.Errorf("Get request failed: %s", resp.Status)
		os.Exit(1)
	}

	var comic ComicData

	if err := json.NewDecoder(resp.Body).Decode(&comic); err != nil {
		resp.Body.Close()
		fmt.Errorf("Failed to parse body: %s", err)
		os.Exit(1)
	}

	
	currentComics := comic.Num
	resp.Body.Close()
	return currentComics
}


func buildIndex(comics int) {
	// Index --> Comic Data
	indexOfComics := make(map[int]ComicData)

	// Transcript -> Index
	TranscriptIndexes := make(map[string]int)

	f, err := os.Create("index.txt")

	if err != nil {
		fmt.Errorf("Failed to create index file in buildIndex: %s", err)
		os.Exit(1)
	}

	for i := 1; i < comics; i++ {
		url := fmt.Sprintf("https://xkcd.com/%d/info.0.json", i)
		fmt.Printf("Processing Comic #%d\n", i)


		resp, err := http.Get(url)

		if err != nil {
			log.Fatal(err)
			continue
		}

		if resp.StatusCode != http.StatusOK {
			resp.Body.Close()
			fmt.Errorf("Get request %d failed: %s", i, resp.Status)
			continue
		}

		var comic ComicData

		if err := json.NewDecoder(resp.Body).Decode(&comic); err != nil {
			resp.Body.Close()
			fmt.Errorf("Failed to parse body: %s", err)
			continue
		}

		indexOfComics[i] = comic; 
		TranscriptIndexes[comic.Transcript] = i; 
	}

	data := Comics{
		ComicIndex: indexOfComics,
		TranscriptIndexes: TranscriptIndexes,
	}

	jsonData, err := json.Marshal(data)
	if err != nil {
			log.Fatalf("failed to marshal: %v", err)
	}
	fmt.Println(string(jsonData))

	if _, err := f.WriteString(string(jsonData)); err != nil {
		log.Fatal(err)
	}
}
