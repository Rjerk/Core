package main

import "fmt"

type Vertex struct {
    Lat, Long float64
}

var m = map[string]Vertex {
    "Bell Labs": {40.1111, 50.2222},
    "Google": {37.1111, 20.1111},
}

func main() {
    fmt.Println(m)
}
