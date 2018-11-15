module Main exposing (UserStatus(..))

type UserStatus
    = Regular
    | Visistor


type alias User =
    { status : UserStatus
    , name : String
    }


thomas =
    { status = Regular, name = "Thomas" }


kate95 =
    { status = Visitor, name = "kate95" }
represent all this with just a single custom type:
type User
    = Regular String
    | Visitor String


thomas =
    Regular "Thomas"


kate95 =
    Visitor "kate95"

type User
    = Regular String Int
    | Visitor String


thomas =
    Regular "Thomas" 44


kate95 =
    Visitor "kate95"



type User
    = Regular String Int Location
    | Visitor String
    | Anonymous



---


type Msg
    = PressedEnter
    | ChangedDraft String
    | ReceivedMessage { user : User, message : String }
    | ClickedExit



---


type Profile
    = Failure
    | Loading
    | Success { name : String, description : String }
