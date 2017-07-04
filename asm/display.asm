data segment
    QQ db ?
data ends

code segment
    assume ds:data, cs:code

start:
    mov ax, data
    mov ds, ax
    mov al, [QQ]
    cmp al, 100
    jnc dispM
    mov dl, 'M'
    mov ah, 2
    int 21h
    jmp enddisp

dispM:
    mov dl, 'N'
    mov ah, 2
    int 21h
    jmp enddisp

enddisp:
    mov ax, 4c0h
    int 21h

code ends
end start