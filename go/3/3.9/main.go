// Webserver to allow users to edit mandelbrot set fractal
package main

import (
	"net/http"
	"log"
	"image"
	"image/color"
	"image/png"
	"math/cmplx"
	"strconv"
)

const (
	width, height = 1024, 1024
)


func main() {
	http.HandleFunc("/", func (w http.ResponseWriter, r *http.Request) {
		var xmin, ymin, xmax, ymax float64 = -2, -2, +2, +2

		params := r.URL.Query()

		if len(params["xmin"]) > 0 {
			val, err := strconv.ParseFloat(params["xmin"][0], 64)
			if err != nil {
				httpErr(w, "Error: xmin not valid")
			}
			xmin = val
		}

		if len(params["xmax"]) > 0 {
			val, err := strconv.ParseFloat(params["xmax"][0], 64)

			if err != nil {
				httpErr(w, "Error: xmax not valid")
			}
			xmax = val

		}

		if len(params["ymin"]) > 0 {
			val, err := strconv.ParseFloat(params["ymin"][0], 64)
			if err != nil {
				httpErr(w, "Error: ymin not valid")
			}
			ymin = val

		}

		if len(params["ymax"]) > 0 {
			val, err := strconv.ParseFloat(params["ymax"][0], 64)
			if err != nil {
				httpErr(w, "Error: ymax not valid")
			}
			ymax = val

		}
		
		if xmin > xmax || ymin > ymax {
			httpErr(w, "Error: xmin and ymin must be smaller than xmax and ymax")
		}

		makeImg(w, xmin, xmax, ymin, ymax)
	})
	log.Fatal(http.ListenAndServe("localhost:8000", nil))
}

func httpErr(w http.ResponseWriter, message string) {
	http.Error(w, message, http.StatusInternalServerError)

}

func makeImg(w http.ResponseWriter, xmin float64, xmax float64, ymin float64, ymax float64) {
 
	img := image.NewRGBA(image.Rect(0, 0, width, height))

	for py := 0; py < height; py++ {
		y := float64(py) / height * (ymax - ymin) + ymin
		for px := 0; px < width; px++ {
			x := float64(px) / width * (xmax-xmin) + xmin
			z := complex(x, y)
			img.Set(px, py, mandelbrot(z))
		}
	}
	png.Encode(w, img)
}

func mandelbrot(z complex128) color.Color {
	const iterations = 200
	const contrast = 15

	var v complex128
	for n := uint8(0); n < iterations; n++ {
		v = v*v+z
		if cmplx.Abs(v) > 2 {
			return color.Gray{255 - contrast * n}
		}
	}
	return color.Black
}