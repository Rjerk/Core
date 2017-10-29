package main

import (
    "fmt"
    "math"
)

func main() {
    var x, y int = 3, 4
    var f float64 = math.Sqrt(float64(x*x+y*y))
    var z uint = uint(f)

    fmt.Println(x, y, z)

    a := 23
    b := float64(a)
    c := uint8(a)

    fmt.Println(a, b, c)
}
