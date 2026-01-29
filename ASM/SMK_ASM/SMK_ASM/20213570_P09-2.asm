TITLE Practice09-2
INCLUDE Irvine32.inc

.data
count = 3
array WORD count DUP(?)

.code
main proc
	push OFFSET array         ;EBP = 00B8F7FC, ESP = 00B8F7EC        
	push COUNT ;EBP = 00B8F7FC, ESP = 00B8F7E8        
	
	call ArrayFill ;EBP = 00B8F7FC, ESP = 00B8F7E4, EIP = 00603687        
	mov esi,OFFSET array ;ESI = 00606000        
	mov ecx,count ;ecx = 00000003        
	mov ebx,2 ;ebx = 00000002        
	call DumpMem
	exit
main endp

ArrayFill PROC
	push ebp ;EBP = 00B8F7FC, ESP = 00B8F7E0        
	mov ebp,esp ;EBP = 00B8F7E0, ESP = 00B8F7E0        
	pushad ;EBP = 00B8F7E0, ESP = 00B8F7C0        
	mov esi,[ebp+12]         ; ESI = 00606000        
	mov ecx,[ebp+8] ; ecx = 00000003        
	cmp ecx,0 ; ECX < 0?
	jle L2 ; yes: skip over loop
L1:
	mov eax,10000h ; eax = 00010000     
	call RandomRange
	mov [esi],eax
	add esi,TYPE WORD; ESI = 00606002 00606004 00606006
	loop L1
L2: 
	popad ;EBP = 00B8F7E0, ESP = 00B8F7E0        
	pop ebp ;EBP = 00B8F7FC, ESP = 00B8F7E4        
	ret 8 ; clean up the ArrayFill stack
ArrayFill ENDP
END main