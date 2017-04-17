#!/bin/bash

# this is a bash program

funWithReturn()
{
    echo "the funtion is to get the sum of two number."
    read -p "input first number: " num1
    read -p "input second number: " num2
    echo "the two num are $num1 and $num2."
    return $(($num1+$num2))
}

funWithReturn
ret=$?
echo "sum = $ret"

