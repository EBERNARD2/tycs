#lang racket
; Write a procedure squares that takes a sentence of numbers as its argument and
; returns a sentence of the squares of the numbers:

; base case is determining string length  if 0 return senctence
; else recursively call string iterator with char squared and added to sentence

(define (square-strings x)
  (define (string-square x)
  (* (string->number x) (string->number x)))

  (define (add-number-to-sentence string-num sentence)
  (if (string=? " " string-num)
      sentence
      (string-append sentence " " (number->string (string-square string-num)))))

  (define (string-iter str sentence)
    
  (if (= 0 (string-length str))
      sentence
      (string-iter (substring str 1) (add-number-to-sentence (substring str 0 1) sentence))))
  
  (string-iter x "")
  )

(square-strings "2 3 4 5")


