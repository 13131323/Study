INCLUDE Irvine32.inc
 .data
  string DWORD 30 DUP(?)
 .code
 InputName PROC C
  mov ecx, LENGTHOF string                    ; ECX: 0000001E, EIP: 00C04135
  mov esi, OFFSET string                      ; ESI: 00C0C000, EIP: 00C0413A
 L1 :
  call ReadChar                               ; EAX: 0000266C, ECX: 0000001E , EIP: 00C0413F
  mov [esi], eax                              
  add esi, 4                                  ; ESI: 00C0C004, EIP: 00C04144 
  cmp al, 30h                                 ; EIP: 00C04146 
  je L2                                       ; Jump Condition
  loop L1
 L2 :
  ret
 InputName ENDP
 PrintName PROC C
  mov ecx, LENGTHOF string                   ; ECX: 0000001E, EIP: 00C04150
  mov esi, OFFSET string                     ; ESI: 00C0C000, EIP: 00C04155
 L1 :
  mov eax, [esi]                             ; EAX: 0000266C, EIP: 00C04157
  cmp al, 30h                                ; EAX: 0000266C, EIP: 00C04159 
  je L2                                      
  call WriteChar
  add esi, 4                                 ; ESI: 00C0C004, EIP: 00C04163
  loop L1                                    ; ECX: 0000001D, EIP: 00C04155
 L2 :
  ret
 PrintName ENDP
 END