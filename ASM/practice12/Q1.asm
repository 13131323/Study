 TITLE Practice12-1
 INCLUDE Irvine16.inc
 .data
    strALTF1 BYTE "ALT + F1", 0dh, 0ah, 0
    strShiftF1 BYTE "Shift + F1",0dh, 0ah, 0
    strCtrlP BYTE "Ctrl + P", 0dh, 0ah, 0
 .code
 main PROC
    mov ax, @data
    mov ds, ax
    call ClrScr
 L1 :
    mov ah, 10h
    int 16h
    cmp al, 1Bh ; ¡®ESC¡¯
    je return
    cmp ah, 68h
    jne L2
    mov dx, OFFSET strALTF1
    call WriteString
 L2 :
    cmp ah, 54h
    jne L3
    mov dx, OFFSET strShiftF1
    call WriteString
 L3 :
    cmp ax, 1910h
    jne L1
    mov dx, OFFSET strCtrlP
    call WriteString
    jmp L1
 return:
    exit
 main ENDP
 END main