package main 


import (
	"fmt"
	"time"
)

var pc [256]byte

func init() {
	for i := range pc {
		pc[i] = pc[i / 2] + byte(i&1)
	}
}

func main() {
	num := uint64(12345678)

	start := time.Now()
	PopCountExp(num)
	end := time.Now()

	elapsedExp := end.Sub(start)


	start = time.Now()
	PopCountLoop(num)
	end = time.Now()

	elapsedLoop := end.Sub(start)

	fmt.Printf("Expression time: %d. Loop time: %d\n", elapsedExp, elapsedLoop)

}

func PopCountExp(x uint64) int {
	return int(pc[byte(x>>(0*8))] +
		pc[byte(x>>(1*8))] +
		pc[byte(x>>(2*8))] +
		pc[byte(x>>(3*8))] +
		pc[byte(x>>(4*8))] +
		pc[byte(x>>(5*8))] +
		pc[byte(x>>(6*8))] +
		pc[byte(x>>(7*8))])
}

func PopCountLoop(x uint64) int {
	sum := 0

	for i := 0; i < 8; i++ {
		sum += int(pc[byte(x>>(i*8))])
	}

	return sum
}