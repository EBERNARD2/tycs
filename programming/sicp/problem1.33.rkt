#lang racket

 (require math/number-theory)

;; accumulator function (accumulate combine null-value term a next b)


;; functions for sum

;; combine function - sum

(define (add x y) (+ x y))

;; null-value for sum 
(define (null-value-for-sum) 0) 


;; addition term
(define (identity x) x)

;; sqaured term
(define (sqr x) (* x x))

;; cube term
(define (cube-num x) (* x x x))

;; pi sum term

(define (pi-sum-term x) (/ 1.0 (* x (+ x 2))))


;; next for sum addition and cubes

(define (next-sum x) (+ 1 x))

;; next for pi sum
(define (next-pi x) (+ x 4))




;; Functions for product
;; combine function - product

(define (product x y) (* x y))


;; null-value for product 
(define (null-value-for-product) 1)



;; term for product

(define (product-identity x) x)



; next value for product
(define (next-val-for-product x) (+ x 1))






; range


;is prime function

(define (is-prime? x) (prime? x))

;; filtered accumulate function

(define (filtered-accumulate combine null-value term a next b filter-func)
  (cond
    [(> a b) (null-value)]
    [(filter-func a) (combine (term a) (filtered-accumulate combine null-value term (next a) next b filter-func))]
    [else (filtered-accumulate combine null-value term (next a) next b filter-func)]))



(filtered-accumulate add null-value-for-sum sqr 1 next-sum 10 is-prime?)