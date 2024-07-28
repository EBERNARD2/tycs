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
	temp := ""
	
	n := len(s)
	if n <= 3 {
		return s
	}


	for ; n >= 0; n -= 3 {
		temp = string(s[n]) + temp
		temp = string(s[n - 1]) + temp
		temp = string(s[n - 2]) + temp
		temp = "," + temp
	}

	buf.WriteString(temp)
	return buf.String()
}