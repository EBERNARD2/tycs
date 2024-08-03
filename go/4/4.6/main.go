package main

import (
	"unicode"
	"fmt"
)

func main() {

	y := []byte{byte('\f'), byte('\n'), byte('a'), byte('b'), byte('c'),}
	fmt.Println(y)
	y = adjancentRunes(y)
	fmt.Println(y)
}


func adjancentRunes(s []byte) []byte {
	currentIdx := 0 

	for i := 0; i < len(s); i++ {
		r := rune(s[i])

		if unicode.IsSpace(r) {
			for unicode.IsSpace(r) && i < len(s) - 1 {
				i++
				r = rune(s[i])
			}

			s[currentIdx] = byte(32)
			currentIdx++
		} else {
			s[currentIdx] = s[i]
			currentIdx++
		}
	}
	currentIdx++
	return s[:currentIdx]
}

