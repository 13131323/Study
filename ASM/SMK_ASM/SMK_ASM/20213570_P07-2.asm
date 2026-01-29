 TITLE Practice07 - 2
 INCLUDE Irvine32.inc
 .data
 InvalidInputMsg BYTE 0Dh, 0Ah, "Invalid input", 0Dh, 0Ah, 0
 .code
 main PROC
 call Clrscr
 StateA :
 call GetNext
 cmp al, 'x'	; starts with 'x' ?
 je StateB		; go to State B if equal
 call DisplayErrorMsg
 jmp Quit
 StateB :
 call GetNext
 call IsAtoY
 jz StateB		; go to State B if ZF == 1
 cmp al, 'z'	; ends with 'z' ?
 je StateC		; go to State C if equal
 call DisplayErrorMsg
 jmp Quit
 StateC:
 Quit:
 call Crlf
 exit
 main ENDP
 IsAtoY PROC
 cmp al, 'a'
 jb ID1
 cmp al, 'y'
 ja ID1
 test ax, 0
 ID1:
 ret
 IsAtoY ENDP
 GetNext PROC
 call ReadChar
 call WriteChar
 ret
 GetNext ENDP
 DisplayErrorMsg PROC
 push edx
 mov edx, OFFSET InvalidInputMsg
 call WriteString
 pop edx
 ret
 DisplayErrorMsg ENDP
 END main