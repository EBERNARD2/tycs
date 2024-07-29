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
	
	commaIdx := n % 3

	for i, v := range s { 
		if commaIdx == i && commaIdx < n{
			buf.WriteByte(',')
			commaIdx += 3
		}
		buf.WriteRune(v)
	}

	return buf.String()
}