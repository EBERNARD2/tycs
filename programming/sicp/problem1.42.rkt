#lang racket


(define (sqaure x) (* x x))
(define (inc x) (+ 1 x))


(define (compose f g)
  (lambda (x) (f (g x))))

((compose sqaure inc) 6)

