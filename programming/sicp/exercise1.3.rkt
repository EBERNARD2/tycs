#lang racket

; Exercise 1.3 SICP
;(define (square-larger x y z)
; input: 10 5 2
; expected output: 125

(define (square x) (* x x))

(define (sum-of-square x y)
  (+ (square x) (square y)))


(define (sum-of-squares-two-largest x y z)
  (cond ((or (> x y z) (> y x z)) (sum-of-square x y))
        ((or (> x z y) (> z x y)) (sum-of-square x z))
        (else (sum-of-square y z))
        ))



(sum-of-squares-two-largest 10 5 2)



(define (a-plus-abs-b a b)
  ((if (> b 0) + -) a b))



