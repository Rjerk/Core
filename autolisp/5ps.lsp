(defun C:5ps ( / #os1 #p ent i l1 n p1 pt1 ss x)
 (setvar "cmdecho" 0)
 (setvar "blipmode" 0)
 (vl-load-com) ;;加载vlax扩展函数
 (setq #os1 (getvar "osmode"))
 (setq pt1 (getpoint "\n请指定五角星中心点"))
 (if (/= pt1 nil)
  (progn
   (setq L1 (getdist "\n请输入五角星外切圆半径"))
   (while (<= L1 0) (setq L1 (getdist "\n请输入五角星外切圆半径")) )
   (if (/= L1 nil)
    (progn
     (setvar "osmode" 0)
     (command "polygon" 5 pt1 "I" L1);绘制一个正5边形
     (setq ent (entlast));取得这个对象
     (setq #p (mapcar 'cdr (vl-remove-if '(lambda (X) (/= 10 (car x))) (entget ent))));取得多段线里面的点
     (entdel ent);正五边形删除
     (setq ss (list 2 4 1 3);多段线取点顺序
           i 0
           p1 (car #p)
     )
     (command "PLINE" p1);绘制多段线
     (repeat 4
      (setq n (nth i ss)
            p1 (nth n #p)
      )
      (command p1)
      (setq i (+ i 1))
     )
     (command "c")
     (command "Circle" pt1 L1);如果不绘制外切圆这句话删除
     (setvar "osmode" #os1)
    )
   )
  )
 )
 (prin1)
);复制到记事本以【.lsp】为后缀命名，命令为：WJX;autoLISP程序