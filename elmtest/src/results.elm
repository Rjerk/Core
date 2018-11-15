module Main exposing (isReasonableAge)

--- give additional information when things go wrong:
--- type Result error value
---   = Ok value
---   | Err error


isReasonableAge : String -> Result String Int
isReasonableAge input =
    case String.toInt input of
        Nothing ->
            Err "That't not a number!"

        Just age ->
            if age < 0 then
                Err "Please try again after you are born."

            else if age > 135 then
                Err "Are u some kind of turtle?"

            else
                Ok age



-- isReasonableAge "abc" == Err ...
-- isReasonableAge "-13" == Err ...
-- isReasonableAge "24"  == Ok 24
-- isReasonableAge "150" == Err ...


type Error
    = BadUrl String
    | Timeout
    | NetworkError
    | BadStatus Int
    | BadBody String



-- Ok "All happy ..." : Result Error String
-- Err Timeout        : Result Error String
-- Err NetworkError   : Result Error String
