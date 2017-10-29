package main

import (
    //"golang.org/x/tour/wc"
    "strings"
    "fmt"
)

func WordCount(s string) map[string]int {
    m := make(map[string]int)
    set := strings.Fields(s)

    for _, v := range set {
        m[v]++
    }

    fmt.Println(m)
    return m
}

func main() {
    WordCount("1 2 3");
    //wc.Test(WordCount)
}
