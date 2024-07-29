package main

import "fmt"


func main() {
	fmt.Println(isAnagram("hello", "goodbye"))
	fmt.Println(isAnagram("hello", "hello"))
	fmt.Println(isAnagram("hello", "Hello"))
	fmt.Println(isAnagram("france", "france"))
}

func isAnagram(s1, s2 string) bool {
	// { c: 1, a: 1, t:1}
	charsFound := makeMap(s1)
	
	for _, r := range s2 {
		currentRune := string(r)
		if _, ok := charsFound[currentRune]; ok && charsFound[currentRune] > 0 {
			charsFound[currentRune]--
		}
	}
	sum := 0
	for k := range charsFound {
		sum += charsFound[k]
	}

	return len(s1) == len(s2) && sum == 0
}


func makeMap(s string) map[string]int {
	output := make(map[string]int)
	
	for _, r := range s {
		output[string(r)]++
	}
	return output
}