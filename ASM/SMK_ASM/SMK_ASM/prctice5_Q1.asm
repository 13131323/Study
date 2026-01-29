TITLE Practice05-1
 INCLUDE Irvine32.inc
 .data
    aName BYTE "Jonghwa", 0              ; Write your name in the blank
    nameSize = ($ - aName) - 1                   ; nameSize == 7   
.code
 main PROC
    ;push the name on the stack
    mov ecx, nameSize                            ; ECX == 00000007h
    mov esi, 0                                   
L1: ; Write how the values of ESI, ESP, EAX, and ECX change in your report
    movzx eax, aName[esi]                         
    push eax                                      
    inc esi                                       
    loop L1                                      ; ECX == 7->6->5->4->3->2->1 h 
    ; pop the name from the stack, in reverse,
    ; and store in the aName array.
    mov ecx, nameSize
    mov esi, 0
 L2: ; Write how the values of ESI, ESP, EAX, and ECX change in your report
    pop eax
    mov aName[esi], al
    inc esi
    loop L2
 exit
 main ENDP
 END main