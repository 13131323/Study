TITLE Practice 11-3
 .model small
 .stack 100h
 .386
      bufferSize = 20
 .data
      buffer BYTE bufferSize + 1 DUP(0);
 .code
 main PROC
      mov ax, @data
      mov ds, ax
      mov esi, 0
      mov dh, 0
      mov dl, 1
      mov bl, 71h
 L1:
      mov ah, 10h
      int 16h
      cmp al, 0dh
      je L2
      mov buffer[esi], al
      mov ah, 9h
      mov bh, 0h
      mov cx, 1h
      int 10h
      mov ah, 3h
      mov bh, 0h
      int 10h
      mov ah, 2h
      mov bh, 0
      inc dl
      int 10h
      inc esi
      inc bl
      jmp L1
 L2 :
      .EXIT
 main ENDP
 END main