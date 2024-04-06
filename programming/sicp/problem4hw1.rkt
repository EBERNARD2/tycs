#lang racket

 

;; procedures needed

(define (first sentence word)
  (if (or (= 0 (string-length sentence)) (string=? " " (substring sentence 0 1)))
      word
      (first (substring sentence 1) (string-append word (substring sentence 0 1)))))


(define (but-first sentence)
  (cond
    [(string=? " " (substring sentence 0 1)) (substring sentence 2)]
    [(string=? (substring sentence 0 1)) "" sentence]
    [else  (but-first (substring sentence 1))]))
;; iterator through sentence

(define (order-iter sentence)
  (if (= 0 (string-length sentence))
      #t
      (cond
        [(current-num-less-than-next-num sentence) (order-iter (but-first sentence))]
        [else #f])))

;; way to grab current and next number

(define (current-num-less-than-next-num sentence)
  (if (string=? "" (first (but-first sentence) ""))
      #t
  (< (string->number (first sentence "")) (string->number (first (but-first sentence) "")))))

;; way to convert strings into numbers

;; way to compare numbers to each other



; grab two numbers

; if number 1 is less than number two continue

; if not return false

; continue until all numbers completed

