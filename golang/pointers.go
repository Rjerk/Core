package main

import "fmt"

func main() {
    i, j := 23, 270

    p := &i
    fmt.Println(*p)

    *p = 222
    fmt.Println(i)

    p = &j
    *p = *p / 37
    fmt.Println(j)
}
