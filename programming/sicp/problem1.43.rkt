#lang racket

(define (compose f g)
  (lambda (x) (f (g x))))


(define (sqrr x) (* x x))
(define (repeated f num)
  (if (= num 1)
      f
      (compose f (repeated f (- num 1)))))

((repeated sqrr 2))

(define (repeat-sqr x n)
 (if (= x 1) n
     (* n (repeat-sqr (- x 1) n))))

(define (repeat-sum x n)
 (if (= x 1) n
     (+ n (repeat-sum (- x 1) n))))


 


 

