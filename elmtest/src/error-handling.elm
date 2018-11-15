module Main exposing (User)

--- use custom types like Maybe to make failure explicit
--- when you see a Maybe String, the compiler will ensure that both variants are accounted for.
--- This way you get the same flexibility, but without the surprise crashes
--- Maybe type is defined like this:
--- type Maybe a
---   = Just a
---   | Nothing


type alias User =
    { name : String
    , age : Maybe Int
    }



--- type alias Friend =
---     { name : String
---     , age : Maybe Int
---     , height : Maybe Float
---     , weight : Maybe Float
---     }
--- Avoid Overuse
--- If you find yourself using Maybe everywhere, it is worth examining your type and type alias definitions
--- to see if you can find a more precise representation. This often leads to a lot of nice refactors in your update and view code!


type Friend
    = Less String
    | More String Info


type alias Info =
    { age : Int
    , height : Float
    , weight : Float
    }


sue : User
sue =
    { name = "Sue"
    , age = Nothing
    }


tom : User
tom =
    { name = "Tom"
    , age = Just 24
    }


canBuyAlcohol : User -> Bool
canBuyAlcohol user =
    case user.age of
        Nothing ->
            False

        Just Age ->
            age >= 21
