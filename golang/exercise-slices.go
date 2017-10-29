package main

import (
    "fmt"
    //"golang.org/x/tour/pic"
)

func Pic(dx, dy int) [][]uint8 {
    s := make([][]uint8, dy)
    fmt.Println("len:", len(s))

    for x := range s {
        s[x] = make([]uint8, dx)
        for y := range s[x] {
            s[x][y] = uint8(x^y)
        }
        fmt.Println(s[x])
    }

    return s
}

func main() {
    Pic(10, 10)
    //pic.Show(Pic)
}
