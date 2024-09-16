package main


import "fmt"

type IntSet struct {
	words []int
}

func (s *IntSet) Add(x int) {
	s.words = append(s.words, x)
}

func (s *IntSet) AddAll(vals ...int) int {
	var sum int
	for _, num := range vals {
		sum += num
	}

	return sum
}


func main() {
	ints := IntSet{ words: make([]int, 1, 2 )}

	ints.Add(10)
	ints.Add(9)

	fmt.Println(ints.AddAll(ints.words...))
}