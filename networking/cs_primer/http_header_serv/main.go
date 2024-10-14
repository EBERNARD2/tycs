package main

import (
	"syscall"
)

func main() {
	syscall.Socket(syscall.AF_INET, syscall.SOCK_STREAM, syscall.IPPROTO_IPIP)
}
