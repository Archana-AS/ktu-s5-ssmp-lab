assume cs:code,ds:data
data segment
    g1 db 0dh,0ah,"Enter the count: $"
    g2 db 0dh,0ah,"Enter the array: $"
    g3 db 0dh,0ah,"The array is given below : $"
    g4 db 0dh,0ah,"Enter the search element: $"
    msg1 db 0dh,0ah," found: $"
    msg2 db 0dh,0ah," not found: $"
    nl db 0dh,0ah,"$"
    ar db 10 dup(0)
data ends


disps macro msg
    lea dx,msg
    mov ah,09h
    int 21h
endm

readc macro
    mov ah,01h
    int 21h
endm

code segment
start:
    mov cx,data
    mov ds,cx
    
    disps g1
    readc
    sub al,30h
    mov cl,al
    mov ch,al
    mov bh,al
    lea si,ar
    disps g2
     
loop1:
   disps nl
   readc
   sub al,30h
   mov [si],al
   inc si
   dec cl
   jnz loop1
   
   disps g4
   readc
   
   sub al,30h
   
   lea si,ar
   mov dl,ch

up:
  mov bl,[si]
  cmp al,bl
  jz fo
  inc si
  dec dl
  jnz up
  disps msg2
  jmp end1
 
fo:
  disps msg1
 
end1:
    mov ah,4ch
    int 21h
    code ends
    end start