;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname intro) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(require 2htdp/universe)
(require 2htdp/image)

(define WIDTH 200)
(define HEIGHT 400)

(define ROCKET (overlay (circle 10 "solid" "green") (rectangle 40 4 "solid" "green")))
(define ROCKET-CENTER-TO-TOP
  (- HEIGHT (/ (image-height ROCKET) 2) 10))

(define ROCK-BED
(rectangle (/ WIDTH 4) 10 "solid" "brown"))


(define MIDDLE-VIEW
  (/ WIDTH 2))

(define (picture-of-rocket t)
  (cond
    [(<= t ROCKET-CENTER-TO-TOP)
     (place-image ROCKET MIDDLE-VIEW t (overlay/align "middle" "bottom" ROCK-BED (empty-scene WIDTH HEIGHT)))]
    [(> t  ROCKET-CENTER-TO-TOP)
     (place-image ROCKET MIDDLE-VIEW ROCKET-CENTER-TO-TOP (overlay/align "middle" "bottom" ROCK-BED (empty-scene WIDTH HEIGHT)))]
    ))



(picture-of-rocket 66660)



