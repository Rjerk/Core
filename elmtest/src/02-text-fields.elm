module Main exposing (Model, main)

import Browser
import Html exposing (Attribute, Html, div, input, text)
import Html.Attributes exposing (..)
import Html.Events exposing (onInput)



--- Main


main =
    Browser.sanbox { init = init, update = update, view = view }



--- Model


type alias Model =
    { content : String }


init : Model
init =
    { content = "" }



--- Update


type Msg
    = Change String


update : Msg -> Model -> Model
update msg model =
    case msg of
        Change newContent ->
            --- update the object
            { model | content = newContent }



--- View


view : Model -> Html Msg
view model =
    div []
        [ input [ placeholder "Text to reverse", value model.content, onInput Change ] []
        , div [] [ text (String.reversse model.content) ]
        ]
