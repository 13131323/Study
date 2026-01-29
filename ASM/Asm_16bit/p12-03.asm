TITLE Practice12-3
 INCLUDE Irvine16.inc
.data
    msg BYTE "Interrupt vector table example", 0dh, 0ah, 0
    handlerMsg BYTE "Keyboard Interrupt Changed.", 0dh, 0ah, 0
 .code
 main PROC
    mov ax, @data
    mov ds, ax
    mov dx, OFFSET msg
    call WriteString ; result: Interrupt vector table example
 install_handler:
    push ds
    mov ax, @code
    mov ds, ax
    mov ah, 25h
    mov al, 09h ;IRQ1: Keyboard Hardware Interrupt
    mov dx, OFFSET keyboard_handler
    int 21h
    pop ds
    
    mov ah, 1
    int 21h
    exit
 main ENDP
 keyboard_handler PROC
    push ax
    push dx
    mov dx, OFFSET handlerMsg
    call WriteString ; result: Keyboard Interrupt Changed.
    pop dx
    pop ax
    iret
 keyboard_handler ENDP
 END main