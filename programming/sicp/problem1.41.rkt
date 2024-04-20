#lang racket


(define (inc x)
  (+ 1 x))

(define (double f)
  (lambda (x) (f (f x))))

 ((double inc) 0)


(((double (double double)) inc) 5)


