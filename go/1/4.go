package main

import (
	"fmt"
	"os"
	"io/ioutil"
	"strings"
)


func main() {
	counts := make(map[string]int)
	output := make(map[string]string)
	files := os.Args[1:]

	for _, filename := range files {
		file, err := ioutil.ReadFile(filename)
		
		if err != nil {
			fmt.Fprintf(os.Stderr, "dup %v\n", err)
			continue
		}

		lineValuesFound := make(map[string]bool)


		for _, line := range strings.Split(string(file), "\n") {
			counts[line]++
			lineValuesFound[line] = true
 		}

		for line := range lineValuesFound {
			output[line] += filename + " "
		}

	}

	for line, files := range output {
		if counts[line] > 1 {
			fmt.Printf("%s\t%s\n", line, files)
		}
	}

}
