module Main exposing (main)

import Browser
import Html exposing (Html, button, div, text)
import Html.Events exposing (onClick)


main =
    Browser.sandbox { init = init, update = update, view = view }



--- Model
--- Now that we have a model, we need to define how it changes over time


type alias Model =
    Int


init : Model
init =
    0



--- Update
--- defining a set of messages that we will get from the UI
--- The Msg type describes these capabilities as data


type Msg
    = Increment
    | Decrement



--- the update function just describes what to do when you receive one of these messages.
--- "update : Msg -> Model -> Model" take a Model argument and return a Model


update : Msg -> Model -> Model
update msg model =
    case msg of
        Increment ->
            model + 1

        Decrement ->
            model - 1



--- View
--- Elm has a library called elm/html that gives you full access to HTML5 as normal Elm functions
--- our view function is producing a Html Msg value


view : Model -> Html Msg



--- div and button are just normal Elm functions. These functions take (1) a list of attributes
--- and (2) a list of child nodes. It is just HTML with slightly different syntax.
--- Instead of having < and > everywhere, we have [ and ]


view model =
    div []
        [ button [ onClick Decrement ] [ text "-" ]
        , div [] [ text (String.fromInt model) ]
        , button [ onClick Increment ] [ text "+" ]
        ]
