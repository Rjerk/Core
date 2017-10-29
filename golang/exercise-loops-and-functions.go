package main

import (
    "fmt"
    "math"
)

func Sqrt(x float64) float64 {
    var z float64 = 5.5
    for {
        z = z - (z*z - x) / (2 * z)
        if math.Abs(z*z - x) < 0.00000000001 {
            break
        }
    }
    return z

}

func main() {
    fmt.Println(Sqrt(32))
    fmt.Println(math.Sqrt(32))
}
