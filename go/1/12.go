package main

import (
	"math"
	"math/rand"
	"image"
	"image/color"	
	"image/gif"
	"net/http"
	"log"
	"strings"
	"strconv"
	"io"
	"fmt"
)


var palette = []color.Color{color.Black, color.RGBA{0x13, 0x00, 0xFF, 0xFF}}

func main() {
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
	splitUrl := strings.Split(r.URL.Path, "cycles=")
	url := splitUrl[0]

	if len(splitUrl) > 1 {
		url = splitUrl[1]
	}
 
	cycles, err := strconv.Atoi(url); 
	
	if err != nil {
		fmt.Fprintf(w, "err: %v", err)
	}
	
	lissajous(w, cycles)
	})

	log.Fatal(http.ListenAndServe("localhost:8000", nil))
}


func lissajous(out io.Writer, cycles int) {
	const (
		res 	 	= 0.001
		size 	 	= 100
		nframes	= 64
		delay   = 8
	)

	freq := rand.Float64() * 3.0
	anim := gif.GIF{LoopCount: nframes}
	phase := 0.0

	for i := 0; i < nframes; i++ {
		rect := image.Rect(0, 0 , 2 * size + 1, 2 * size + 1)
		img := image.NewPaletted(rect, palette)
		colorIdx := uint8(0)

		for t := 0.0; t < float64(cycles) * 2 * math.Pi; t += res {
			x := math.Sin(t)
			y := math.Sin(t *freq + phase)
			img.SetColorIndex(size + int(x * size + 0.5), size + int(y * size + 0.5), colorIdx)
			colorIdx++

			if colorIdx == 4 {
				colorIdx = uint8(0)
			}
		}
		phase += 0.1
		anim.Delay = append(anim.Delay, delay)
		anim.Image = append(anim.Image, img)
 	}
	gif.EncodeAll(out, &anim)
}