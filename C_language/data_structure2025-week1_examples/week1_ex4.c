/*
 * swap 예제 #2
 */

#include <stdio.h>

int main(int argc, char **argv) {
    int a = 10;
    int b = 20;
    int temp;

    printf("before swap: a :%d, b :%d\n", a, b);
    temp = a;   // a의 값을 읽어서 (10) 잠시 다른 곳에 저장
    a = b;      // b의 값을 읽어서 (20) a에 저장
    b = temp;   // 임시로 저장한 값 (10)을 b에 저장
    printf("after swap: a :%d, b :%d\n", a, b);

    return 0;
}