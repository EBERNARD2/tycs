#lang racket

;; inc to next value
(define (inc x) (+ x 1))


;; get current value
(define (current val) val)


(define (prod x y) (* x y))
;; take product

(define (product term a next b)
  (if (> a b)
      1
      (* (current a) (product term (next a) next b))))


(product current 1 inc 10)