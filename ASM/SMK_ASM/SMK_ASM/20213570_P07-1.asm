TITLE Practice07-1 
INCLUDE Irvine32.inc
 ENTER_KEY = 13
 .data
 InvalidInputMsg BYTE 0Dh, 0Ah, "Invalid input", 0Dh, 0Ah, 0
 .code
 main PROC
 call Clrscr
 StateA :
 call GetNext
 cmp al, '+'
 je StateB
 cmp al, '-'
 je StateB
 call IsDigit
 jz StateC
 call DisplayErrorMsg
 jmp Quit
 StateB :
 call GetNext
 call IsDigit
 jz StateC
 call DisplayErrorMsg
 jmp Quit
 StateC :
 call GetNext
 call IsDigit
 jz StateC
 cmp al, ENTER_KEY
 je Quit
 call DisplayErrorMsg
 jmp Quit
 Quit :
 call Crlf
 exit
 main ENDP
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
