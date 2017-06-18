assume cs : codesg, ds : datasg

datasg segment
db 'BaSic'
db 'MiNix'
datasg ends

codesg segment

start:

mov bx, 0
mov cx, 5

s1:
    mov al, [bx]
    and al, 11011111b
    mov [bx], al
    mov al, [5+bx]
    or  al, 00100000b
    mov [5+bx], al
    inc bx
    loop s1

    mov ax, 4c00h
    int 21h
codesg ends

end start
