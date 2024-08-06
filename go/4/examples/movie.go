package main

import(
	"fmt"
	"encoding/json"
)

type Movie struct {
	Title string
	Year int `json:"released"`
	Color bool `json:"color,omitempty"`
	Actors []string
}


var movies = []Movie{
	{Title: "Casablanca", Year: 1842, Color: false,
				Actors: []string{"Humphrey Bogart", "Ingrid Bergman"}}
}

func main() {
	data, err := json.MarshalIdent(movies, "", "    ")

	if err != nil {
		log.Fatalf("Json Marshalling failed: %s\n", err)
	}

	fmt.Printf("%s\n", data)
}