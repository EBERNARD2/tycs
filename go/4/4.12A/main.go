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
	Transcript string `json:"tanscript"`
	Alt 			 string `json:"alt"`
	Img				 string `json:"img"`
	Title 		 string `json:"title"`
	Day 			 string `json:"day"`
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


func buildIndex(comicNum int) {
	for i := 1; i < comicNum; i++ {
		url := fmt.SprintF("https://xkcd.com/%d/info.0.json", i)

		esp, err := http.Get(url)

		if err != nil {
			log.Fatal(err)
			os.Exit(1)
		}

		if resp.StatusCode != http.StatusOK {
			resp.Body.Close()
			fmt.Errorf("Get request %d failed: %s", i, resp.Status)
			os.Exit(1)
		}

	}
}
