 TITLE Practice08-2 
INCLUDE Irvine32.inc
 .data
 .code

 ;main Procedure
 main PROC
     ; Shift left
     mov al, 8Fh      ; AL = 8Fh
     shl al, 1        ; CF = 1, AL = 1Eh
     mov bl, 1000000b 
     shl bl, 2        ; CF = 1, BL = 00h
     mov cx, 10h      
     shl cx, 4        ; CX = 0100h, multiply by 2^4
    ; Shift Right
    mov al, 00000010b
    shr al, 2        ; CF = 1, AL = 00h
    mov bx, 400h
    shr bx, 4        ; BX = 0040h, divide by 2^4
    ; Shift Arithmetic Left, Right
    mov eax, 0FF80h  ; EAX = 0000FF80h
    sal eax, 16      ; EAX = FF800000h
    sar eax, 16      ; EAX = FFFFFF80h
    ; Rotate Left, Right
    mov ax, 6A4Bh    
    rol ax, 4        ; AX = A4B6h
    ror ax, 4        ; AX = 6A4Bh
    ; Rotate Carry Left, Right
    clc         ; set carry flag to 0
    mov bl, 88h ; CF = 0, BL = 88h
    rcl bl, 1   ; CF = 1, BL = 10h
    rcl bl, 1   ; CF = 0, BL = 21h
    stc         ; set carry flag to 1
    mov cl, 10h ; CL = 10h, CF = 1
    rcr cl, 1   ; CL = 88h, CF = 0
 exit
 main ENDP
 END main