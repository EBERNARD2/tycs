package main

import (
	"time"
	"log"
)



func main() {
	bigSlowOperation()
}

func bigSlowOperation() {
	defer trace("big slow operation")()
	// do a bunch of work
	time.Sleep(10 * time.Second)
}

func trace(msg string) func() {
	start := time.Now()
	log.Printf("enter %s", msg)
	return func() { log.Printf("exit %s (%s)", msg, time.Since(start)) }
}