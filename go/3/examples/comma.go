package main

import "fmt"

func main() {
	fmt.Println(comma("12345"))
	fmt.Println(comma("5596997060050"))
}

func comma(s string) string {
	n := len(s) // Hello World
	if n <= 3 {
		return s
	}

	return comma(s[:n-3]) + "," + s[n-3:]

}