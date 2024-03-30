;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname chapt3notes) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))


(define (ff a)
  (* a 10))

(define (distance-to-origin x y)
(sqrt (+ (sqr x) (sqr y))))



(define (string-first s)
  (substring s 0 1))


(define (===> x y )
  (or (not x) y))


(===> #true #false)