(defun C:diamonds()
    (setq osmd (getvar "osmode")) (setq colr (getvar "cecolor"))
    (setq cen (getpoint "POSITION: "))
    (setq rad (getreal "RADIUS: "))
    (setq len (/ rad (* 2 (sin (/ (* 3 pi) 8))))) 
    (setq d 0)
    (repeat 4
        (setvar "CEcolor" "blue")
        (command "pline" cen (polar cen (+ (/ pi 8) d) len)
            (polar cen (+ 0 d) rad) (polar cen (+ (* pi 1.875) d) len) "c")
        (command "hatch" "solid" "L" "")
        (setq d (+ d (/ pi 2)))
    )
    (setq d 0)
    (repeat 4
        (setvar "CEcolor" "green")
        (command "pline" cen (polar cen (+ (/ pi 8) d) len)
            (polar cen (+ (/ pi 4) d) rad) (polar cen (+ (* pi 0.375) d) len) "c")
        (command "hatch" "solid" "L" "")
        (setq d (+ d (/ pi 2)))
    )
    (setvar "osmode" osmd) (setvar "cecolor" colr)
)