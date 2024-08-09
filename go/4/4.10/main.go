package main

import (
	"fmt"
	"log"
	"os"
	"gopl.io/ch4/github"
	"time"
)

type categories struct {
	lessThanMonth []*Issue
	lessThanYear  []*Issue
	moreThanYear	[]*Issue
} 

func main() {
	result, err := github.SearchIssues(os.Args[1:])
	if err != nil {
		log.Fatal(err)
	}
	fmt.Printf("%d issues:\n", result.TotalCount)
	for _, item := range result.Items {
		fmt.Printf("#%-5d %9.9s %.55s\n",
			item.Number, item.User.Login, item.Title)
	}
}


func makeCategories() *categories {
	var categorizedIssues  *categories
	categorizedIssues = new(categories)

	timeNow = time


}
