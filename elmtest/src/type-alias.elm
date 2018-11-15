module Main exposing (User)


type alias User =
    { name : String
    , bio : String
    }


hasDecentBio : User -> Bool
hasDecentBio user =
    String.length user.bio > 80


updateBio : String -> User -> User
updateBio bio user =
    { user | bio = bio }



--- User "Tome" "Friendly Carpenter"
