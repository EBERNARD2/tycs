package main


import "fmt"


func main() {

	fmt.Println(retNonZeroVal())
}


func retNonZeroVal() (val string) {
	defer func() {
		val = fmt.Sprintf("Eror: %v", recover())
	}()

	panic("I'm panicking")
}