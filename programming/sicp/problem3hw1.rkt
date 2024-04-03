#lang racket
;Write a procedure switch that takes a sentence as its argument and returns a sentence
; in which every instance of the words I or me is replaced by you, while every instance of
; you is replaced by me except at the beginning of the sentence, where it’s replaced by I.
; (Don’t worry about capitalization of letters.) Example:
; > (switch ’(You told me that I should wake you up))
; (i told you that you should wake me up)


;(define (switch sentence))

(define (switch sentence)
  (define (first-word? word)
  (string=? "" word))

 (define (but-first sentence)
  (if (char-whitespace? (substring sentence 0 1))
      (substring sentence 1)
      (but-first (substring sentence 1))))

  (define (first sentence word)
    (if (or (= 0 (string-length sentence)) (string=? " " (substring sentence 0 1)))
      word
      (first (substring sentence 1) (string-append word (substring sentence 0 1)))))

  (define (is-word-you? word)
  (or (string=? word "you") (string=? word "You") (string=? word "YOU")))

  (define (is-word-first-person? word)
  (or (string=? word "me") (string=? word "Me") (string=? word "ME")
   (string=? word "i") (string=? word "I")))
  
(define (new-sentence input output)
   (cond
    [(= 0 (string-length input)) output]
    [(and (first-word? output) (is-word-you? (first input ""))) (new-sentence (substring input 3) (string-append output "I"))]
    [(is-word-you? (first input "")) (new-sentence (substring input 3) (string-append output "me"))]
    [(is-word-first-person? (first input "")) (new-sentence (substring input 2) (string-append output "you"))]
    [else (new-sentence (substring input 1) (string-append output (substring input 0 1)))]))

  (new-sentence sentence "")
  )






(define (is-word-first-person? word)
  (or (string=? word "me") (string=? word "Me") (string=? word "ME")
   (string=? word "i") (string=? word "I")))

;; helper to determine if word is you
(define (is-word-you? word)
  (or (string=? word "you") (string=? word "You") (string=? word "YOU")))

; helper procedure to get first word in a sentence
; recursively call procedure to find first space then return sentence
(define (first sentence word)
  (if (or (= 0 (string-length sentence)) (string=? " " (substring sentence 0 1)))
      word
      (first (substring sentence 1) (string-append word (substring sentence 0 1)))))

;; helper procedure to return everything in a sentence but the first word
(define (but-first sentence)
  (if (char-whitespace? (substring sentence 0 1))
      (substring sentence 1)
      (but-first (substring sentence 1))))


;; helper to determine if it is the first word in a sentence 
(define (first-word? word)
  (string=? "" word))


(define (new-sentence input output)
   (cond
    [(= 0 (string-length input)) output]
    [(and (first-word? output) (is-word-you? (first input ""))) (new-sentence (substring input 3) (string-append output "I"))]
    [(is-word-you? (first input "")) (new-sentence (substring input 3) (string-append output "me"))]
    [(is-word-first-person? (first input "")) (new-sentence (substring input 2) (string-append output "you"))]
    [else (new-sentence (substring input 1) (string-append output (substring input 0 1)))]))



(switch "You told me that I should wake you up")

