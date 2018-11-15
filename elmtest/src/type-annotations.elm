module Main exposing (half)

--- 1. Error Message Quality
--- When you add a type annotation, it tells the compiler what you are trying to do.
--- Your implementation may have mistakes, and now the compiler can compare against your stated intent.
--- 2. Documentation
--- When you revisit code later (or when a colleague visits it for the first time),
--- it can be really helpful to see exactly what is going in and out of the function without having
--- to read the implementation super carefully.


half : Float -> Float
half n =
    n / 2


hypotenuse : Float -> Float -> Float
hypotenuse a b =
    sqrt (a ^ 2 + b ^ 2)


checkPower : Int -> String
checkPower powerLevel =
    if powerLevel > 9000 then
        "It's over 9000!!!"

    else
        "Meh"
