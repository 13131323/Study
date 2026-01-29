TITLE Practice08-1
 INCLUDE Irvine32.inc
 .data
     arrayD DWORD 10000h, 20000h, 30000h
 .code
 main PROC
     push ebp                                  ; ebp = 003DFDFCh
     mov ebp, esp                              ; esp = 003DFDF8h
     mov esi, OFFSET arrayD                    ; esi = 00B06000h
     mov ecx, LENGTHOF arrayD                  ; ecx = 00000003h
     push ecx
     call ArraySum
     pop ebp
     call WriteHex
     call Crlf
 exit
 main ENDP
 ArraySum PROC
     push ebp                                  ; ebp = 003DFDECh
     mov ebp, esp                              ; esp = 003DFDE0h
     mov ecx, [esp+8]                          ; ecx = 00000003h
 L1:;input array to stack
     push [esi]                                ; esi = 00B06000h   00B06004h   00B06008h
     add esi, 4  
     loop L1
     mov ecx, [esp+20]                         ; ecx = 00000003h
     mov eax, 0
 L2:;add stack
     pop ebx                                   ; ebx = 00030000h   00020000h    00010000h
     add eax, ebx                       
     loop L2
     pop ebp
     ret 4
 ArraySum ENDP
 END main
