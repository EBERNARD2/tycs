package main


import (
	"fmt"
	"os"
	"bufio"
	"strconv"
)

type Fahrenheit float64
type Celsius float64
type Feet float64
type Meters float64
type Pounds float64
type Kilograms float64


func main() {
	if len(os.Args) > 1 {
		for _, val := range os.Args[1:] {
			printComparisons(val)
		}
	} else {
		input := bufio.NewScanner(os.Stdin)

		for input.Scan() {
			printComparisons(input.Text())
		}
	}
}

func printComparisons(s string) {
	val, err := strconv.ParseFloat(s, 64)

	if err != nil {
		fmt.Fprintf(os.Stderr, "comparisons: %v\n", err)
		os.Exit(1)
	}

	fmt.Printf("Fahrenheit: %g  Celsius: %g\n", val, FToC(Fahrenheit(val)))
	fmt.Printf("Feet: %g  Meters: %g\n", val, FToM(Feet(val)))
	fmt.Printf("Pounds: %g  Kilograms: %g\n", val, PToK(Pounds(val)))

}

func FToC(f Fahrenheit) Celsius { return Celsius((f - 32) * 5 / 9)}
func FToM(f Feet) Meters { return Meters(f * .3048) }
func PToK(p Pounds) Kilograms { return Kilograms(p * 2.205)}
