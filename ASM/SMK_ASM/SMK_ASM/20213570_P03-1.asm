 TITLE Practice03-2
 INCLUDE Irvine32.inc
 .data
    byteList BYTE 10h, 20h, 30h, 40h
    byteListSize = ($ - byteList)
    wordList WORD 1000h, 2000h, 3000h, 4000h
    wordListSize = ($ - wordList)
    dwordList DWORD 10000000h, 20000000h, 30000000h, 40000000h
    dwordListSize = ($ - dwordList)
 .code
 main PROC
    mov eax, byteListSize  ; EAX: ????????h
    mov ebx, wordListSize  ; EBX: ????????h
    mov ecx, dwordListSize ; ECX: ????????h
    call DumpRegs
 exit
 main ENDP
 END main
