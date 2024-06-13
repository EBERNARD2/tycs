#lang racket


(define (double f)
  ((f) (f)))


(define (inc x)
  (+ x 1))

