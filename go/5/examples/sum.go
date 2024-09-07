package main

import "fmt"


func main() {

	vals := []int{2,5,6,6}
	fmt.Println(sum(1,2,3,45,6,7,78,8,10))
	fmt.Println(sum(vals...))



}

func sum(vals ...int) int {
	total := 0
	for _, val := range vals {
		total += val
	}

	return total
}