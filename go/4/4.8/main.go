package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"unicode"
)

func main() {
	counts := map[string]int{
		"letter": 0,
		"digits": 0,
		"numbers": 0,
		"symbol": 0,
		"spaces": 0,
	}

	invalid := 0
	in := bufio.NewReader(os.Stdin)
	
	for {
		r, n, err := in.ReadRune()

		if err == io.EOF {
			break
		}

		if err != nil {
			fmt.Fprintf(os.Stderr, "charcount: %v\n", err)
			os.Exit(1)
		}

		if unicode.IsLetter(r) && n > 1{
			counts["letter"]++
		}

		if unicode.IsDigit(r) && n > 1{
			counts["digits"]++
		}

		if unicode.IsSymbol(r) && n > 1{
			counts["symbol"]++
		}

		if unicode.IsSpace(r) && n > 1{
			counts["spaces"]++
		}

		if unicode.IsNumber(r) && n > 1{
			counts["numbers"]++
		}
	}

	fmt.Println("Counts")

	for k, v := range counts {
		fmt.Printf("%s occurences\t\t%d\n", k, v)
	}

	if invalid > 0 {
		fmt.Printf("\n invalid UTF-8 characters\n", invalid)
	}
}