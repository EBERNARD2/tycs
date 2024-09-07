package main


import (
	"fmt"
	"log"
)




func main() {
	 fmt.Println(max(-500, 10, 200, -10000, 2345, 545, 133, 40))
	 fmt.Println(min(-500, 10, 200, -10000, 2345, 545, 133, 40))
}	 


func max(vals ...int) int {
	if len(vals) == 0 {
		log.Fatalf("Max: Must pass slice of values to function\n")
	}

	currentMax := vals[0]

	for _, v := range vals[1:] {

		if v > currentMax {
			currentMax = v
		}
	}

	return currentMax
} 

func min(vals ...int) int {
	if len(vals) == 0 {
		log.Fatalf("Min: Must pass slice of values to function\n")
	}

	currentMin := vals[0]

	for _, v := range vals[1:] {

		if v < currentMin {
			currentMin = v
		}
	}

	return currentMin
}