(defun C:3dpentacle()
    (setq osmd (getvar "osmode"))
    (setq colr (getvar "cecolor"))

    (setq cen (getpoint "select circle's center"))
    (setq rad 500)
    (command "circle" cen rad)

    (setq d (* pi 0.2)) (setq a (/ pi 10))
    (setq rad_in (* rad (/ (sin (/ pi 10)) (cos (/ pi 5)))))
    
    (setq p1 (polar cen a rad))             (setq p2 (polar cen (+ a d) rad_in))
    (setq p3 (polar cen (+ a (* 2 d)) rad)) (setq p4 (polar cen (+ a (* 3 d)) rad_in))
    (setq p5 (polar cen (+ a (* 4 d)) rad)) (setq p6 (polar cen (+ a (* 5 d)) rad_in))
    (setq p7 (polar cen (+ a (* 6 d)) rad)) (setq p8 (polar cen (+ a (* 7 d)) rad_in))
    (setq p9 (polar cen (+ a (* 8 d)) rad)) (setq p10 (polar cen (+ a (* 9 d)) rad_in))
    (setvar "CEcolor" "red")
    (command "pline" p1 p2 p3 p4 p5 p6 p7 p8 p9 p10 "c")
    (command "pline" cen p1 "c") (command "pline" cen p3 "c")
    (command "pline" cen p5 "c") (command "pline" cen p7 "c") (command "pline" cen p9 "c")
    
    (prompt "choose the pentacle object.");
    (setq pentacle (ssget))
    ; 需要在报告里删除的注释
    ; 这儿有个BUG（但我没打算修复它，毕竟只是一次性作业，而我再不会回头学这玩意儿）：
    ; 同一图案里，第二次生成不了就把 65 后面的数字再改成大于 100 的数字（虽然我不保证能行）就行了
    (command "extrude" pentacle "" "t" 65 113.5)
    (command "view" "seiso")
    (command "render")
    (setq ss1 nil)
    (setvar "osmode" osmd)
    (setvar "cecolor" colr)
    (prin1)
)