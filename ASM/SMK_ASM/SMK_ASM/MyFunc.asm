.386
.model flat
.code
_Func PROC
	push ebp ; ESP = 00CFF990, EBP = 00CFFA84
	mov ebp, esp ; ESP = 00CFF990, EBP = 00CFF990
	sub esp, 12 ; ESP = 00CFF984
	mov DWORD PTR[ebp - 4], 2
	mov DWORD PTR[ebp - 8], 4
	mov DWORD PTR[ebp - 12], 8
	mov eax, [ebp+8]          ; EAX = 0000000A
	mul DWORD PTR[ebp - 4] ; EAX = 00000014
	mov ebx, eax          ; EBX = 00000014
	mov eax, [ebp+12]          ; EAX = 00000002
	mul DWORD PTR[ebp-8]          ; EAX = 00000008
	add eax, ebx          ; EAX = 0000001C
	sub eax, [ebp-12]          ; EAX = 00000014
	add esp, 12          ; ESP = 00CFF990
	pop ebp          ; ESP = 00CFF994  EBP = 00CFFA84
	ret
_Func ENDP
END