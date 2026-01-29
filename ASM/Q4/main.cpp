//main.cpp
//-----------------------------------
#include <stdio.h>
int Multiplication(int n, int m);     //Function prototype
int main(void) {
    int n = 9;
    int m = 3;
    printf_s("Multiplication %d * %d = %d\n", n, m, Multiplication(n, m));
    return 0;
}
int Multiplication(int n, int m) {
    int retValue = 0;
    __asm {
        mov ecx, n                 // ECX : 00000009, EAX : 7B79E445.
        mov eax, m                // ECX : 00000009, EAX : 00000003.
        mul ecx                    // ECX : 00000009, EAX : 0000001B.
        mov retValue, eax          // ECX : 00000009, EAX : 0000001B.
    }
    return retValue;
}