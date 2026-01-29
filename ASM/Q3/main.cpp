//main.cpp
 //-----------------------------------
#include <stdio.h>
int Sum(int n);     //Function prototype
int main(void) {
	int n = 9;
	printf_s("Sum 1 ~ %d = %d\n", n, Sum(n));
	return 0;
}
int Sum(int n) {
	int retValue = 0;
	__asm {
		mov ecx, n                 // ECX : 00000009, EAX : 3FFD3B6A.
		mov eax, 0                 // ECX : 00000009, EAX : 00000000.
		L1:
		add eax, ecx                // ECX : 00000009 00000008 ..., EAX : 00000009 00000011....
			loop L1                     // ECX : 00000008 00000007..., EAX : 00000009 00000011....
			mov retValue, eax          // ECX : 00000000, EAX : 0000002D.
	}
	return retValue;
}