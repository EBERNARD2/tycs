package main


import (
	"fmt"
	"os"
	"encoding/json"
	"log"
	"strings"
	"net/http"
	// "image"
)

type Movie struct {
	Title        string                   
  Year         string   
  Rated        string   
  Released     string              
  Runtime      string     
  Genre        string       
  Director     string                  
  Writer       string                    
  Actors       string                   
  Plot         string                  
  Language     string          
  Country      string               
  Awards       string    
  Poster       string                   
  Metascore    string       
  imdbRating   string        
  imdbVotes    string       
  imdbID       string           
  Type         string    
  DVD          string 
  BoxOffice    string       
  Production   string        
  Website      string     
  Response     string                     
} 

func main() {
	if len(os.Args) == 1 {
		log.Fatalf("Usage: filename {search query}\n")
		os.Exit(1)
	}

	movie := getData(strings.Join(os.Args[1:], " "))

	printPosterImg(movie)
}


func getData(movie string) *Movie{
	url := fmt.Sprintf("http://www.omdbapi.com/?apikey=ab60e53e&t=%s", movie)

	resp, err := http.Get(url)

	if err != nil {
		fmt.Fprintf(os.Stderr, "Error fetching movie: %v\n", err)
		os.Exit(1)
	}

	if resp.StatusCode != http.StatusOK {
		resp.Body.Close()
		fmt.Fprintf(os.Stderr, "Error fetching movie: %v\n", err)
		os.Exit(1)
	}

	var movieData Movie

	if err := json.NewDecoder(resp.Body).Decode(&movieData); err != nil {
		resp.Body.Close()
		fmt.Fprintf(os.Stderr, "Error decoding movie data: %v\n", err)
		os.Exit(1)
	}
	
	return &movieData
}


func printPosterImg(movie *Movie) {

	resp, err := http.Get(movie.Poster)

	if err != nil {
		fmt.Fprintf(os.Stderr, "Error fetching poster image: %v\n", err)
		os.Exit(1)
	}

	if resp.StatusCode != http.StatusOK {
		resp.Body.Close()
		fmt.Fprintf(os.Stderr, "Error fetching poster image: %v\n", err)
		os.Exit(1)
	}

	// img, _, err := image.Decode(resp.Body)
	 
	// if err != nil {
	// 	log.Fatal(err)
	// }


	var b []byte

	if err := json.NewDecoder(resp.Body).Decode(&b); err != nil {
		resp.Body.Close()
		fmt.Fprintf(os.Stderr, "Error decoding poster image: %v\n", err)
		os.Exit(1)
	}

 
	fmt.Printf("%v\n", b)
	// fmt.Println(resp.Body)
}
