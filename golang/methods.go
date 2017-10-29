package main


import (
    "fmt"
    "math"
)

type Vertex struct {
    X, Y float64
}

// 方法接受者在func关键字和方法名之间的参数中
func (v *Vertex) Abs() float64 {
    return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

func main() {
    v := &Vertex{3, 4}
    fmt.Println(v.Abs())
}
