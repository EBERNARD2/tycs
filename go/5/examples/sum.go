package main

import "fmt"


func main() {

	fmt.Println(sum(1,2,3,45,6,7,78,8,10))

}

func sum(vals ...int) int {
	total := 0
	for _, val := range vals {
		total += val
	}

	return total
}