#lang racket


;; accumulator function (accumulate combine null-value term a next b)


;; functions for sum

;; combine function - sum

(define (add x y) (+ x y))

;; null-value for sum 
(define (null-value-for-sum) 0) 


;; addition term
(define (identity x) x)

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



;; accumulator function 

(define (accumulate combine null-value term a next b)
  (if (> a b)
      (null-value)
      (combine (term a) (accumulate combine null-value term (next a) next b))))



; addition
(accumulate add null-value-for-sum identity 1 next-sum 10)

; sum cubes

(accumulate add null-value-for-sum cube-num 1 next-sum 10)

; pi sum
(accumulate add null-value-for-sum pi-sum-term 1 next-sum 10)


; product range
(accumulate product null-value-for-product product-identity 1 next-sum 10)
