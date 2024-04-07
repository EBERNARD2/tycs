#lang racket
; Write a procedure ends-e that takes a sentence as its argument and returns a sentence
;      containing only those words of the argument whose last letter is E:
;  given: please put the salami above the blue elephant
;  return : (please the above the blue)

(define (ends-e sentence)
  (define (last word)
  (substring  word (- (string-length word) 1) (string-length word)))
  
  (define (word-ends-with-e? word)
  (or (string=? "E" (last word)) (string=? "e" (last word))))

  (define (get-next-word sentence word)
  (if (or (string=? "" sentence) (string=? " " (substring sentence 0 1)))
      word
      (get-next-word (substring sentence 1) (string-append word (substring sentence 0 1)))))

  (define (but-first sentence)
  (cond
    [(string=? "" sentence) sentence]
    [(string=? " " (substring sentence 0 1)) (substring sentence 1)]
    [else  (but-first (substring sentence 1))] 
    ))

  (define (sentence-iter sentence output-sentence)
  (if (string=? "" sentence)
      output-sentence
      (cond
        [(word-ends-with-e? (get-next-word sentence "")) (sentence-iter (but-first sentence)(string-append output-sentence " " (get-next-word sentence "")))]
        [else (sentence-iter (but-first sentence) output-sentence)])))

  (sentence-iter sentence "")
 )



(ends-e "please put the salami above the blue elephant")

; iterate through sentence -> grab a word -> check if word ends with e -> if yes add it to compiled word












