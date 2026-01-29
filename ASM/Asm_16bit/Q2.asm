TITLE Practice 11-2
 INCLUDE Irvine16.inc
 .data
 string BYTE 30 DUP(?)
 .code
 main PROC
   mov   ax, @data
   mov   ds, ax
   call INPUT
   call PRINT
   exit
 main ENDP
 PRINT PROC
   push ebp
   mov ebp, esp
   call Crlf
   mov cl, LENGTHOF string
   mov esi, OFFSET string
 L1 :
   mov ah, 2
   mov dl, [esi]
   cmp dl, 2Eh            ; ASCII code ¡®.¡¯
   je L2
   INT 21h
   inc esi
   loop L1
 L2 :
   pop ebp
   ret
 PRINT ENDP
 INPUT PROC
   push ebp
   mov ebp, esp
   call Clrscr
   mov cl, LENGTHOF string
   mov esi, OFFSET string
 L1 :
   mov ah, 1
   INT 21h
   mov [esi], al
   cmp al, 2Eh            ; ASCII code ¡®.¡¯
   je L2
   inc esi
   loop L1
 L2 :
   pop ebp
   ret
 INPUT ENDP
 END  main