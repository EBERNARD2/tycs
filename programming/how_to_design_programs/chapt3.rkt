;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname chapt3) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(require 2htdp/batch-io)


(define (letter fst lst signature-name)
  (string-append (opening fst) "\n" (body fst lst) "\n\n" (closing signature-name)))

(define (opening first)
  (string-append "Dear " first ", " "\n\n"))

(define (body fst lst)
  (string-append "We have discovered that all people with the" "\n"
    "last name " lst " have won our loterry. So, " "\n"
    fst ", " "huerry and pick up your prize!"))

(define (closing signature-name)
  (string-append "Sincerely," "\n\n" signature-name "\n"))


(define (main in-first in-last in-signature out)
  (write-file out
              (letter
               (read-file in-first)
               (read-file in-last)
               (read-file in-signature))))

(main "first.out" "last.out" "signature.out" 'stdout)