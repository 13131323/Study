/*
 * 함수 내부에서 다른 함수를 호출하는 예제
 */

#include <stdio.h>

void func1(void) {
    printf("func1 called\n");

    printf("func1 finished\n");
}

void func2(void) {
    printf("func2 called\n");

    func1(); // func2에서 func1을 호출

    printf("func2 finished\n");
}

int main(void) {
    printf(" main called\n");

    func2(); // main에서 func2를 호출

    printf(" main finished\n");

    return 0;
}