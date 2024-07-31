package main

import (
	"fmt"
	"crypto/sha256"
)

func main() {
	c1 := sha256.Sum256([]byte("x"))
	c2 := sha256.Sum256([]byte("X"))

	fmt.Printf("c1: %x\nc2: %x", c1, c2)
}


func bitDiff(b1, b2 *[32]byte) int {
	count := 0

	for i := 0; i < 32; i++ {
		val1 := b1[i]
		val2 := b2[i]

		for val1 != 0 {
			
		}
	}
}