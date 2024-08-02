package main 


import "fmt"


func main() {
	s := []int{1, 2, 3,  4, 5, 6}
	s = rotate(s[:], 2)
	fmt.Println(s)

}


func rotate(s []int, n int) []int{
	l := (len(s) - 1) - n

	if n > len(s) {
		l = len(s) % n
	}

	if l == 0 || l == len(s) {
		return s
	}


	dest := make([]int, len(s))

	i := 0 
	for _, v := range s[l + 1:] {
		dest[i] = v
		i++
	}

	for _, v := range s[:len(s) - n] {
		dest[i] = v
		i++
	}

	return dest
}