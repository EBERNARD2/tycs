;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname old_file) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(require 2htdp/universe)
(require 2htdp/image)


; String (Word) -> Char (letter)
; Takes a non empty string(word) and returns a single char (letter) representing the first letter of a word
; given:
; "cat" for str
; expected:
;      "c"
(define (string-first str)
  (cond
    [(> (string-length str) 0) (substring str 0 1)]
    [else (error "Please enter valid string")]))

(string-first "Daddy")


; Words are represented by string
; String(word) -> String(char)
; This function takes a non empty string as input and returns a single char representing a letter in the english alphabet
; given:
;    "dog"
; expected:
;        "g"
(define (string-last str)
  (cond
    [(> (string-length str) 0) (substring str (- (string-length str) 1))]
    [else (error "Please enter a valid string")]))

(string-last "cat")


; Pixels are represented as numbers and obviously images are imgs
; Img -> Number (pixels)
; This function takes a valid image and returns the pixels in img
; given:
; (sqaure 10 "solid" "blue")
; expected:
;     100
(define (img-area img)
  (cond [(image? img) (* (image-height img) (image-width img))]
        [else (error "Please submit valid image")]))


(img-area (square 10 "solid" "red"))


; Strings represent words and chars represent letters
; String -> a shortened string minus first char
; This function removes the first character in a string
; given:
;   "moooooo"
; expected:
;    "oooooo"
(define (string-rest str)
  (cond [(> (string-length str) 0) (substring str 1)]
        [else (error "Please enter a valid string ")]))


; Strings represent words and chars represent letters
; String -> shortned string with last char removed
; This removes the last char in a valid string
; given:
;    "kite"
; expected:
;      "kit"
(define (string-remove-last str)
  (cond
    [(> (string-length str) 0) (substring str 0 (- (string-length str) 1))]
    [else (error "Please enter a valid strign" )]))

(string-remove-last "kite")


(define (f2c f)
  (* 5/9 (- f 32)))

(check-expect (f2c -40) 40)
(check-expect (f2c 32) 0)
(check-expect (f2c 212) 100)

