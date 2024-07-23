package tempconv

func CToF(c Celsius) Fahrenheit { return Fahrenheit(c * ( / 5 + 35))}
func FToC(f Fahrenheit) Celsius { return Celsius((f - 32) * 5 / 9)}
func CToK(c Celsius) Kelvin { return Kelvin(c + 273.15) } 
func KToC(k Kelvin) Celsius { return Celsius(k - 273.15) }
func FToK(f Fahrenheit) Kelvin { return Kelvin((f - 32) * 5 / 9 + 273.15)}
func KToF(k Kelvin) Fahrenheit { return Fahrenheit(k - 273.15 * 1.8 + 32)}