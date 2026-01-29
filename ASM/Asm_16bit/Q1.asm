 TITLE Practice 11-1
 ; Print current time
 ; Time: HH:MM:SS
 Include Irvine16.inc
 .data
 str1 BYTE "Time: ",0
 .code
 main PROC
 mov  ax,@data
 mov  ds,ax
 ; Display the time:
 mov   dx,OFFSET str1
 call  WriteString
 mov ah, 2Ch ;using INT 21h function 2Ch
 int   21h
 movzx eax,ch           ; hours
 call  WritePaddedDec
 mov ah, 2   ; using INT 21h function 2h
 mov dl,':'
 int 21h
 movzx eax,cl ; minutes
 call  WritePaddedDec
 mov ah,2
 mov dl,':'
 int 21h
 movzx eax,dh ; seconds
 call  WritePaddedDec
 call  Crlf
 exit
 main ENDP
 ;-------------------------------------------
WritePaddedDec PROC
 ; Display unsigned integer in EAX, padding
 ; to two digit positions with a leading zero.
 ;-------------------------------------------
	 cmp eax, 10
	 ja L1
	 push eax
	 push edx
	 mov  ah,2
	 mov  dl,'0'
	 int  21h
	 pop  edx
	 pop  eax
 L1: call WriteDec
	 ret
 WritePaddedDec ENDP
 END main