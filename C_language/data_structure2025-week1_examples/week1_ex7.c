/*
 * 일반 자료형 및 포인터 자료형의 크기 비교
 */

#include <stdio.h>

int main(void) {
    int a; short b; char c;
    double d; float f;

    int *p; short *q; char *r;
    double *s; float *t;

    printf("sizeof(int): %d bytes\n", sizeof(int));       // 4 bytes
    printf("sizeof(short): %d bytes\n", sizeof(short));   // 2 bytes
    printf("sizeof(char): %d bytes\n", sizeof(char));     // 1 byte
    printf("sizeof(double): %d bytes\n", sizeof(double)); // 8 bytes
    printf("sizeof(float): %d bytes\n", sizeof(float));   // 4 bytes

    printf("sizeof(int *): %d bytes\n", sizeof(int *));       // 8 bytes in 64bit
    printf("sizeof(short *): %d bytes\n", sizeof(short *));   // 8 bytes in 64bit
    printf("sizeof(char *): %d bytes\n", sizeof(char *));     // 8 bytes in 64bit
    printf("sizeof(double *): %d bytes\n", sizeof(double *)); // 8 bytes in 64bit
    printf("sizeof(float *): %d bytes\n", sizeof(float *));   // 8 bytes in 64bit

    return 0;
}
