package popcount

import "testing"


var pc [256]byte

func init() {
	for i := range pc {
		pc[i] = pc[i / 2] + byte(i&1)
	}
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
func PopCountClear(x uint64) int {
	i := 0
	for x != 0 {
		x = x & (x - 1)
		i++
	}
	return i
}

func bench(b *testing.B, f func(uint64) int) {
	for i := 0; i  < b.N; i++ {
		f(uint64(i))
	}
}

func BenchmarkExp(b *testing.B) {
	bench(b, PopCountExp)
}

func BenchmarkLoop(b *testing.B) {
	bench(b, PopCountLoop)
}

func BenchmarkClear(b *testing.B) {
	bench(b, PopCountClear)
}