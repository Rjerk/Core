data segment

    grade dw 95H, 60H, 75H, 92H, 71H, 86H, 54H, 89H, 83H, 76H
    num   equ ($-grade)/2
    org   30H
    s5    dw 0
    s6    dw 0
    s7    dw 0
    s8    dw 0
    s9    dw 0
    s10   dw 0

data ends

stack segment
    stk db 20 dup (0)
    top equ $-stk
stack ends

code segment
    main proc far
    assume cs:code, ds:data, ss:stack

start:
    push ds
    sub ax, ax
    push ax
    mov ax, data
    mov ds, ax
    mov cx, num
    lea bx, grade ; get grade's address
    
compare:
    mov ax, [bx]
    
    cmp ax, 60H
    jc  five_seg
    
    cmp ax, 70H
    jc  six_seg
    
    cmp ax, 80H
    jc  seven_seg
    
    cmp ax, 90H
    jc  eight_seg
    
    cmp ax, 100H
    jne nine_seg
    
    inc s10
    jmp new_loop

five_seg:
    inc s5
    jmp new_loop

six_seg:
    inc s6
    jmp new_loop

seven_seg:
    inc s7
    jmp new_loop

eight_seg:
    inc s8
    jmp new_loop

nine_seg:
    inc s9
    jmp new_loop

new_loop:
    add bx, 2 ; next student's grade
    loop compare ; loop compare until cx - 1 == 0
    
    ret
    main endp

code ends
end start