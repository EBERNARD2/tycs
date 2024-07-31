package main

import (
	"fmt"
	"crypto/sha256"
)

func main() {
	c1 := sha256.Sum256([]byte("x"))
	c2 := sha256.Sum256([]byte("X"))

	fmt.Println(bitDiff(c1, c2))
}

func PopCount(x uint8) int {
	i := 0
	for x != 0 {
		x = x & (x - 1)
		i++
	}
	return i
}

func bitDiff(b1, b2 [32]byte) int {
	count := 0

	for i := 0; i < 32; i++ {
		val1 := PopCount(b1[i])
		val2 := PopCount(b2[i])

		if val1 > val2 {
			count += val1 - val2
		} else if val2 > val1 {
			count += val2 - val1
		} 
	}

	return count
}