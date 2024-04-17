#lang racket

;; inc to next value
(define (inc x) (+ x 1))


;; get current value
(define (current val) val)


(define (prod x y) (* x y))
;; take product

;;

(define (greater x y) (> x y))

(define (product term a next b comparison)
  (if (comparison a b)
      1
      (* (term a) (product term (next a) next b comparison))))


(product current 1 inc 10 greater)



;; use product for factorial function

;; add a decrement function

(define (dec x) (- x 1))

(define (equal? x y) (= x y))

(product current 7 dec 1 equal?)




