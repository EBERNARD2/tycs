package main


import (
	"fmt"
	"log"
)



func main() {
	str := []string{ "T", "h", "e"}
	fmt.Println(Join("", str...))
	fmt.Println(Join("-", "the", "cat", "ran", "up", "the", "tree"))

}

func Join(sep string, s ...string) string {
	if len(s) == 0 {
		log.Fatalf("Join: Must pass slice of string to join function\n")
	}

	output := ""

	for _, str := range s {
		output += str + sep
	}

	return output[:len(output) - len(sep)]

}