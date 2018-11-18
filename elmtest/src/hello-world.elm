module Main exposing (main)

import Html exposing (div, span, text)
import Html.Attributes exposing (class)



--- main =
---     text "hello, world"


main =
    div [ class "hello" ] [ span [] [ text "hello, world" ] ]
