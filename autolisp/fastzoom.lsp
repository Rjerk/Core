(defun c:zs() (command "zoom" "0.8x") (prin1))

(defun c:zz() (command "zoom" "1.25x") (prin1))

(defun c:za() (command "zoom" "all") (prin1))

(defun c:ze() (command "zoom" "e") (prin1))

(prompt "input zs, zz, za, ze as zoom operation.")
(prin1)