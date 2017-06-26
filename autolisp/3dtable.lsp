(defun C:3dtable()
    (setq osmd (getvar "osmode"))
    (setq colr (getvar "cecolor"))

    ;(setq cen (getpoint "choose the table centre: ")) ; 1200, 600
    ;(setq rad (getreal "input the table radius: ")) ; 300
    (setq cen "1200, 600")
    (command "_circle" cen 150)
    (command "_circle" cen 105)
    (command "_circle" cen  45)
    (command "_circle" "1200,645" 3)
    (command "_array" "1" "" "p" cen 50 360 "y" "")

    (command "_offset" 13 (ssget) "0,0" "")
    
    (command "_circle" "1200,718" 50)
    (command "_array" "1" "" "p" cen  5 360 "y" "")
    
    (command "_trim")
    
    (command "_view" "_swiso")
    (command "_region")
    (command "_extrude" (ssget) 10)

    (command "_extrude" (ssget) 100)
    (command "_hide")
    
    (command "_view" "_front")
    (command "_union")
    (command "_move" (ssget) "" "1200,-10,0" "1200,0,0")
    
    (command "_view" "_swiso")
    
    (command "_extrude" (ssget) "" 1)
    (command "_hide")
    
    (command "_view" "_front")
    (command "_move" (ssget) "" "1200,0,0" "1200,110,0")
    
    (command "fillet" (ssget) 0.5 (ssget) "")
    (command "_array" (ssget) "" "r" 5 1 1)
    
    (command "_union" (ssget "X") "")
    (command "_view" "_swiso")
    (command "_hide")
    
    (setvar "osmode" osmd)
    (setvar "cecolor" colr)
    (prin1)
)