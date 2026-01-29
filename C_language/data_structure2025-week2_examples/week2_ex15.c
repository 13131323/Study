/*
 * C언어 버전에 따른 for loop의 초기식 변수 생성
 */

#include <stdio.h>

/* C90이전 버전은 // 스타일의 한 줄 주석도 지원을 하지 않는다...  */
int main() {
    /* for loop의 초기식에서 변수를 생성하면? */
    for (int i = 0; i < 10; i++) {
        printf("i: %d\n", i);
    }

    /* 해당 C언어 표준을 준수하는지 엄격히 확인하기 위해서는 -pedantic-errors 옵션을 사용한다. */
    /* ex) gcc -o run.exe source.c -std=c89 -pedantic-errors*/
    /*     --> source.c 파일을 run.exe 파일로 컴파일하며, c89 표준으로 컴파일하고 문법을 엄격히 확인 */
    return 0;
}