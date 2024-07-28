package main

import (
	"fmt"
	"bytes"
)

func main() {
	fmt.Println(comma("12345"))
	fmt.Println(comma("5596997060050"))
}

func comma(s string) string {
	var buf bytes.Buffer	
	n := len(s)
	if n <= 3 {
		return s
	}

	sepIdx := len(s) - 4 

	for i, v := range s { 
		if sepIdx % (i + 1) == 0 {
			buf.WriteByte(',')
		}
		buf.WriteRune(v)
	}

	return buf.String()
}