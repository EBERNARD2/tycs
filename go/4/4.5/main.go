package main


import "fmt"

func main() {
	s := []string{ "string", "string", "hi", "no", "goodbye"}
	s = adjacentDups(s)
	fmt.Println(s)

}

func adjacentDups(s []string) [] string{
	lastIdx := 0
	for _, v := range s {
		if v == s[lastIdx] {
			continue
		}

		lastIdx++ 

		s[lastIdx] = v
	}
	lastIdx++
	return s[:lastIdx]
}