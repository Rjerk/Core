(setq snum 1)
(setq s_all 0)
(repeat 100
    (setq s_all (+ snum s_all))
    (setq snum (1+ snum))
)
(princ "1+2+...100= ")
(princ s_all)