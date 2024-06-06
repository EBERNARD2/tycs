#lang racket

(define (square x) (* x x))

(define (average x y)
  (/ (+ x y) 2))

(define (improve guess x)
  (average guess (/ x guess)))

(define (good-enough? guess x)
  (< (abs (- (square guess) x))  0.001))

(define (sqrt-iter guess x)
  (if (good-enough? guess x)
      guess
      (sqrt-iter (improve guess x) x)))

  
(define (sqrt x)
  (sqrt-iter 1.0 x))


(define (iterative-improvement good-enough-guess? improve-guess)
  ((lambda (f) (f f))
  (lambda (iter)
    (lambda (x)
      (if (good-enough-guess? x)
          x
          (iter (improve-guess x)))))))

((iterative-improvement good-enough? improve) 9)