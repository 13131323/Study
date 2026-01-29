/*
 * swap 예제 #1 
 */

#include <stdio.h>

int main(int argc, char **argv) {
    int a = 10;
    int b = 20;

    printf("before swap: a :%d, b :%d\n", a, b);
    a = b;  // b의 값을 읽어서 (20) a에 저장
    b = a;  // a의 값을 읽어서 (??) b에 저장
    printf("after swap: a :%d, b :%d\n", a, b);

    return 0;
}