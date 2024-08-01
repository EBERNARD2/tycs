package main

import "fmt"

func main() {

	s := []string{"hello", "", "goodbye", "", "day", "too"}
	s = nonempty(s[:])
	fmt.Printf("%q\n", s[:])


}

func nonempty(strings []string) []string {
	out := strings[:0]
	for _, s := range strings {
		if s != "" {
			out = append(out, s)
		}
	}
	return out
}

