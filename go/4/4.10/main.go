package main

import (
	"fmt"
	"log"
	"os"
	"gopl.io/ch4/github"
	"time"
)

func main() {
	result, err := github.SearchIssues(os.Args[1:])
	if err != nil {
		log.Fatal(err)
	}
	fmt.Printf("%d issues:\n", result.TotalCount)


	lastMonth := time.Now().AddDate(0, -1, 0)
	lastYear := time.Now().AddDate(-1, 0, 0)

	fmt.Printf("Issues in the last month:\n\n")
	for _, issue := range result.Items {
		if lastMonth.Compare(issue.CreatedAt) == -1 {
			fmt.Printf("#%-5d %9.9s %.55s\n",
				issue.Number, issue.User.Login, issue.Title)
		}
	}

	fmt.Printf("Issues less than a year:\n\n")
	for _, issue := range result.Items {
		if lastYear.Compare(issue.CreatedAt) == -1 && lastMonth.Compare(issue.CreatedAt) == 1 {
			fmt.Printf("#%-5d %9.9s %.55s\n",
				issue.Number, issue.User.Login, issue.Title)
		}
	}

	fmt.Printf("Issues more than a year:\n\n")
	for _, issue := range result.Items {
		if lastYear.Compare(issue.CreatedAt) == 1 {
			fmt.Printf("#%-5d %9.9s %.55s\n",
				issue.Number, issue.User.Login, issue.Title)
		}
	}
}


