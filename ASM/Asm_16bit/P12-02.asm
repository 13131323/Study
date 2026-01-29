TITLE Practice12-2
 INCLUDE Irvine16.inc
 .data
 .code
 main PROC
    mov ax, @data
    mov ds, ax
    call WriteHex ; result:00000225
    call crlf
    mov ax, @code
    call WriteHex ; result:000001A2
    call crlf
    mov ax, OFFSET address1
    call WriteHex ; result:00000027
    call crlf
    mov ax, OFFSET address2
    call WriteHex ; result:00000028 
    exit
 main ENDP
 address1 PROC
    ret
 address1 ENDP
 address2 PROC
    ret
 address2 ENDP
 END main
