package main

import (
	"fmt"
	"strings"
)

func main() {
	fmt.Println(basename2("a/b/c.go"))
	fmt.Println(basename2("c.d.go"))
	fmt.Println(basename2("abc"))
}

func basename2(s string) string {
	slash := strings.LastIndex(s, "/")
	s = s[slash + 1:]
	if dot := strings.LastIndex(s, "."); dot >= 0 {
		s=s[:dot]
	}

	return s
}