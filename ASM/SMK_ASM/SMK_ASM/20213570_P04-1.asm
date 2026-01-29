INCLUDE Irvine32.inc
 .data
 stringL1   BYTE "L1", 0
 stringL2   BYTE "L2", 0
 stringL3   BYTE "L3", 0
 stringL4   BYTE "L4", 0
 stringL5   BYTE "L5", 0
 stringL6   BYTE "L6", 0
 .code
 ;main Procedure
 main PROC
    mov eax, 0A523h                 ; eax = 0000A523h
    cmp eax, 0A523h                 ; eax = 0000A523h
    jne L1
    je L2
    ; Jump to   
    L1 : mov edx, OFFSET StringL1   
         call WriteString
         call Crlf
    L2 : mov edx, OFFSET StringL2
         call WriteString
         call Crlf
    mov cx, 0FFFFh                  ; cx = FFFFh
    inc cx                          ; cx = 0000h
    jnz L3
    jcxz L4
    ; Jump to   
    L3 : mov edx, OFFSET StringL3   
         call WriteString
         call Crlf
    L4 : mov edx, OFFSET StringL4   
         call WriteString
         call Crlf
    mov al, +127                    ; al = 7Fh
    cmp al, -127                    ; al = 7Fh
    jl L5
    jg L6
    ; Jump to   
    L5 : mov edx, OFFSET StringL5   
         call WriteString
         call Crlf
    L6 : mov edx, OFFSET StringL6
         call WriteString
         call Crlf
    exit
 main ENDP
 END main