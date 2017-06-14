(defun c:0()
  (setvar "snapang" 0)
  (prin1)
)

(defun c:15()
  (setvar "snapang" (* i5 (/ pi 180)))
  (prin1)
)

(defun c:30()
  (setvar "snapang" (* 30 (/ pi 180)))
  (prin1)
)

(defun c:45()
  (setvar "snapang" (* 45 (/ pi 180)))
  (prin1)
)

(defun c:60()
  (setvar "snapang" (* 60 (/ pi 180)))
  (prin1)
)

(defun c:75()
  (setvar "snapang" (* 75 (/ pi 180)))
  (prin1)
)

(prompt "enter 0, 15, 30, 45, 60, 75 to set arow.")
(prin1)