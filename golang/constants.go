package main

import "fmt"

const Pi = 3.14

func main() {
    const World = "world"
    fmt.Println("Hello", World)
    fmt.Println("Happy", Pi, "Day")

    const True = true
    fmt.Println("Go rules?", True)
}
