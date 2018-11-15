module Main exposing (Model, main)

import Browser
import Html exposing (Attribute, Html, div, input, text)
import Html.Attributes exposing (..)
import Html.Events exposing (onInput)



--- Main


main =
    Browser.sandbox { init = init, update = update, view = view }



--- Model


type alias Model =
    { content : String }


init : Model
init =
    { content = "" }



--- Update


type Msg
    = Change String



--- pass Msg and Model, return Model
-- looks like update is a function here


update : Msg -> Model -> Model
update msg model =
    case msg of
        --- get newContent, wooooooow
        Change newContent ->
            --- update the model object
            { model | content = newContent }



--- View
--- view is a function, too


view : Model -> Html Msg
view model =
    --- we create a <div> with two children
    div []
        -- input node, placeholder and value attributes
        -- onInput function: the `Change` function is used to tag whatever is currently in the text field
        -- So let's say the text field currently holds glad and the user types e.
        -- This triggers an input event, so we will get the message Change "glade" in our update function.
        [ input [ placeholder "Text to reverse", value model.content, onInput Change ] []
        , div [] [ text (String.reverse model.content) ]
        ]
