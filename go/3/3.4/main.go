// Create server to show svg of surface plot function
package main

import (
	"math"
	"strconv"
	"net/http"
	"log"
)

const (
	width, height 	= 600, 320
	cells						= 100
	xyrange					= 30.0
	xyscale					= width / 2 / xyrange
	zscale 					= height * 0.4
	angle 					= math.Pi / 6
)

var sin30, cos30 = math.Sin(angle), math.Cos(angle)

func main() {
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		surfacePlot()
	})
	log.Fatal(http.ListenAndServe("localhost:8000", nil))
}

func surfacePlot(w http.ResponseWriter) {
	output := ""
	widthStr := "width='" + strconv.Itoa(width) + "' ";
	heightStr := "height='" + strconv.Itoa(height) + "'>";

	output +=  "<svg xmlns= 'http//www.w3.org/2000/svg' "+ 
						 "style='stroke: grey; fill: white; stroke-width: 0.7' "+
						 widthStr + heightStr

	for i := 0; i < cells; i++ {
		for j := 0; j < cells; j++ {
			ax, ay := corner(i+1, j)
			bx, by := corner(i, j)
			cx, cy := corner(i, j+1)
			dx, dy := corner(i+1, j+1)
			
			output += "(<polygon points='" + strconv.FormatFloat(ax, 'g', -1, 64) + "," + strconv.FormatFloat(ay, 'g', -1, 64) +  "," + strconv.FormatFloat(bx, 'g', -1, 64) +
								 "," +strconv.FormatFloat(by, 'g', -1, 64) + "," +strconv.FormatFloat(cx, 'g', -1, 64) + "," +strconv.FormatFloat(cy, 'g', -1, 64) + "," +strconv.FormatFloat(dx, 'g', -1, 64) +
								 "," +strconv.FormatFloat(dy, 'g', -1, 64) + "' />"				
		}
	}
 
	output += "</svg"
	 
}
func corner(i, j int) (float64, float64) {
	x := xyrange * (float64(i) / cells - 0.5)
	y := xyrange * (float64(j) / cells - 0.5)
	z := f(x,y)

	sx := width / 2 + (x - y) * cos30 * xyscale
	sy := height / 2 + (x + 7) * sin30 *xyscale - z * zscale
	return sx, sy
}

func f (x, y float64) float64 {
	r := math.Hypot(x,y)
	return math.Sin(r) / r
}