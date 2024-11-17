assume cs:code,ds:data
data segment
    a db 0ah,0dh,"Enter the first Numbers: $"
    b db 0ah,0dh,"Enter the Second Numbers: $"
    d db 0ah,0dh,"The sum is: $"
data ends

read macro
    mov ah,01h
    int 21h
    sub al,30h
endm

display macro
    add dl,30h
    mov ah,02h
    int 21h
endm

code segment
start:
    mov ax,data
    mov ds,ax

    lea dx,a
    mov ah,09h
    int 21h

    read
    mov dl,10h
    mul dl
    mov bh,al
    read
    add bh,al

    read
    mul dl
    mov bl,al
    read
    add bl,al

    lea dx,b
    mov ah,09h
    int 21h


    read
    mov dl,10h
    mul dl
    mov ch,al
    read
    add ch,al

    read
    mul dl
    mov cl,al
    read
    add cl,al

    lea dx,d
    mov ah,09h
    int 21h

    add bl,cl
    mov al,bl
    daa
    mov bl,al

    jc l1
    jnc l2
l1:
    inc bh
l2:
  add bh,ch
  mov al,bh
  daa
  mov bh,al
 
  jnc next
  mov dl,01h
  display
 
next:
    mov ah,00h
    mov dh,10h
    mov al,bh
    div dh
    mov cx,ax
    mov dl,cl
    display
    mov dl,ch
    display
     
    mov ah,00h
    mov dh,10h
    mov al,bl
    div dh
    mov cx,ax
    mov dl,cl
    display
    mov dl,ch
    display
 
    mov ah,4ch
    int 21h
    code ends
    end start