package parser

import (
	"bufio"
	"bytes"
	"fmt"
)

type HTTPRequest interface {
	Parse()
}

func Parse(b []byte) {
	data := bytes.NewBuffer(b)
	reader := bufio.NewReader(data)

	for {
		line, _, err := reader.ReadLine()

		if err != nil {
			break
		}
		fmt.Println(line)
	}

}

func main() {
	Parse([]byte("GET HTTP / HTTP/1.0\r\n\r\n"))
}
