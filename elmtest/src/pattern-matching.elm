module Main exposing (User(..), toName)


type User
    = Regular String Int
    | Visitor String


toName : User -> String
toName user =
    case user of
        Regular name age ->
            name

        Visitor name ->
            name



--- Wild Cards


toName : User -> String
toName user =
    case user of
        Regular name _ ->
            name

        Visitor name ->
            name



-- toName (Regular "Thomas" 44) == "Thomas"
-- toName (Visitor "kate95")    == "kate95"
