TITLE Registers
 INCLUDE Irvine32.inc
 .code
 main PROC
        mov eax, 11111111h ; EAX : 11111111 EIP : 00033660
        add eax, 33333333h ; EAX : 44444444 EIP : 00033665
        mov ax, 5555h ; EAX : 44445555 EIP : 0003366A
        sub ax, 2222h ; EAX : 44443333 EIP : 0003366E
        mov ah, 99h ; EAX : 44449933 EIP : 00033672
        mov al, 00h ; EAX : 44449900 EIP : 00033674
        sub ax, 11h ; EAX : 444498EF EIP : 00033676
        call DumpRegs ; EAX : 444498EF EIP : 0003367A
        mov ebx, 0              ; EBX : 00000000 EIP : 0003367F
        mov bh, 00h ; EBX : 00000000 EIP : 00033684
        mov bl, 0FFh ; EBX : 000000FF EIP : 00033686
        add bx, 1h ; EBX : 00000100 EIP : 00033688
        call DumpRegs ; EBX : 00000100 EIP : 0003368C
        exit
 main ENDP
 END main
