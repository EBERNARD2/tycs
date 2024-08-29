package main

import (
	"fmt"
	"os"
	"strings"
	"log"
)

const Pre string = "$foo"

func main() {
	if len(os.Args) == 1 {
		log.Fatal("Usage: {filename} {string}")
		os.Exit(1)
	}

	t := expand(os.Args[1], func(s string) { return fmt.Sprintf("hey there %s") })
	fmt.Println(t)
}

func expand(s string, f func(string) string) string {
	w := ""
	for _, c := range s {
		if strings.HasPrefix(Pre, s) {
			s = strings.CutPrefix(s, Pre)
			w += f("you")  
		} else {
			w += c
		}
	}
	return w
}