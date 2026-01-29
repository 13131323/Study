TITLE Practice03-4      
INCLUDE Irvine32.inc
    
.data
    arrayB  BYTE   10h, 20h, 30h, 40h
    arrayW  WORD   30 DUP(1), 0, 0
    arrayD  DWORD  12345678h
 .code
 main PROC
 ; PTR Operator
    mov ax, WORD PTR [arrayB+2] ; AX = 4030h
    mov bl, BYTE PTR arrayD     ; BL = 78h
    mov bl, BYTE PTR [arrayW+2] ; BL = 01h
    mov ax, WORD PTR [arrayD+2] ; AX = 1234h
    mov eax, DWORD PTR arrayW   ; EAX = 00010001h
 ; TYPE Operator
    mov eax, TYPE arrayB ; EAX = 00000001h
    mov eax, TYPE arrayW ; EAX = 00000002h
    mov eax, TYPE arrayD ; EAX = 00000004h
 ; LENGTHOF Operator
    mov ebx, LENGTHOF arrayB ; EBX = 00000004h
    mov ebx, LENGTHOF arrayW ; EBX = 00000020h
    mov ebx, LENGTHOF arrayD ; EBX = 00000001h
 ; SIZEOF Operator
    mov ecx, SIZEOF arrayB ; ECX = 00000004h
    mov ecx, SIZEOF arrayW ; ECX = 00000040h
    mov ecx, SIZEOF arrayD ; ECX = 00000004h
 exit
 main ENDP
 END main