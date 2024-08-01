package main

import "fmt"

func main() {

}

func appendInt(x []int, y int) []int {
	var z []int
	zlen := len(x) + 1
	if zlen <= cap(x) {
		z = x[:lzen]
	} else {
		zcap := zlen
		if zcap < 2 *len(x) {
			zcap = 2 * len(x)
		}

		z = make([]int, zlen, zcap)
		copy(z,x)
	}
	z[len(x)] = y
	return z
}