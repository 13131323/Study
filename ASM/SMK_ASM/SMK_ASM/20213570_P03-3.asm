 TITLE Practice03-3
  
INCLUDE Irvine32.inc
    
.data
    val1  WORD   1000h
    val2  WORD   2000h
    arrayB BYTE  10h, 20h, 30h, 40h, 50h
    arrayW WORD  100h, 200h, 300h
    arrayD DWORD 10000h, 20000h
 .code
 main PROC
 ;  Direct-Offset Addressing (byte array):
    mov al,arrayB    ; AL = 10h
    mov al,[arrayB+4]; AL = 50h
    mov al,[arrayB+2]; AL = 30h
 ;  Direct-Offset Addressing (word array):
    mov ax,arrayW    ; AX = 0100h
    mov ax,[arrayW+4]; AX = 0300h
    mov ax,[arrayW+2]; AX = 0200h
 ;  Direct-Offset Addressing (dword array):
    mov eax,arrayD    ; EAX = 00010000h
    mov eax,[arrayD+4]; EAX = 00020000h
    call DumpRegs
 exit
 main ENDP
 END main