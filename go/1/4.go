package main

import (
	"fmt"
	"os"
	"io/ioutil"
	"strings"
)


func main() {
	counts := make(map[string]int)
	filesfound := make(map[string]string)
	files := os.Args[1:]

	for _, filename := range files {
		file, err := ioutil.ReadFile(filename)
		if err != nil {
			fmt.Fprintf(Stderr, "dup %v\n", err)
			continue
		}

		for _; line := range strings.Split(string(file), "\n") {
			counts[line]++
			filesfound[line] += filename
		}
		
		f.Close()
	}


}

func countlines(f *os.File, counts map[string]int, filesfound map[string]string) {
	input := bufio.NewScanner(f)
	for input.Scan() {
		counts[input.Text()]++
	}
}