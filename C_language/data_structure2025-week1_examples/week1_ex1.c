/*
 * 변수의 값 할당 예제
 */

#include <stdio.h> 

int main(int argc, char **argv) {
    int a;
    int b;

    a = 10;
    b = a;
    b = 20;

    printf("a :%d\n", a);
    printf("b :%d\n", b);

    return 0;
}