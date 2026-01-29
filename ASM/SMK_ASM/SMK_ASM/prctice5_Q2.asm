TITLE Practice05-2
 INCLUDE Irvine32.inc
 .data
    array DWORD 10000h, 20000h, 30000h, 40000h, 50000h
    theSum DWORD ?
 .code
 main PROC
    mov esi, OFFSET array                              ; EIP == 00531025h, ESI == 00534000h 
    mov ecx, LENGTHOF array                            ; EIP == 0053102Ah, ECX == 00000005h
    call ArraySum                                      ; EIP == 0053103Bh, ESP == 00AFFAECh
    mov theSum, eax                                    ; EIP == 00531034h, theSum == 000F0000h
    exit
 main ENDP
 ArraySum PROC
    push esi                                           ; EIP == 0053103Ch, ESP == 00AFFAE8h, ESI == 00534000h
    push ecx                                           ; EIP == 0053103Dh, ESP == 00AFFAE4h, ECX == 00000005h
    mov eax, 0
 L1: ; Write how the values of ESI, ESP, EAX, and ECX change in your report
    add eax, [esi]                                     ; EIP == 00531044h
    add esi, TYPE DWORD                                ; EIP == 00531047h
    loop L1                                            ; EIP == 00531042h
    pop ecx                                            ; EIP == 0053104Ah, ESP == 00AFFAE8h, ECX == 00000005h
    pop esi                                            ; EIP == 0053104Bh, ESP == 00AFFAECh, ESI == 00534000h
    ret                                                ; EIP == 0053102Fh, ESP == 00AFFAF0h
 ArraySum ENDP
 END main