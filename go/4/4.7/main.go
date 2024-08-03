package main 


import "fmt"


func main() {
	s := []byte{0xF0, 0x9F, 0x8E, 0x89}
	s = reverse(s)
	fmt.Println(s)

}


func reverse(s []byte) []byte {
	length := len(s) / 2

	for i, j := 0, len(s) - 1; i < length; i, j = i + 1, j - 1 {
		s[i], s[j] = s[j], s[i]
	}
	return s
}