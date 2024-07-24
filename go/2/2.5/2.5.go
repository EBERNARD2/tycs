package main

import (
	"fmt"
	"time"
)

func main() {
	num := uint64(12345678)

	start := time.Now()
	PopCountClear(num)
	end := time.Now()
	elapsedClear := end.Sub(start)

	fmt.Printf("Clear time: %d answer:%d\n", elapsedClear, PopCountClear(uint64(16)))
}

func PopCountClear(x uint64) int {
	i := 0
	for x != 0 {
		x = x & (x - 1)
		i++
	}
	return i
}