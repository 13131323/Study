/*
 * C언어 버전에 따른 변수 선언 위치 제한
 */

#include <stdio.h>

/* C90이전 버전은 // 스타일의 한 줄 주석도 지원을 하지 않는다...  */
int main() {
    printf("Do something...\n");    /* 어떠한 작업을 수행하고... */
    int var1 = 20;                  /* 변수를 생성하면? */
    printf("Does it work?\n");

    /* 해당 C언어 표준을 준수하는지 엄격히 확인하기 위해서는 -pedantic-errors 옵션을 사용한다. */
    /* ex) gcc -o run.exe source.c -std=c89 -pedantic-errors*/
    /*     --> source.c 파일을 run.exe 파일로 컴파일하며, c89 표준으로 컴파일하고 문법을 엄격히 확인 */
    return 0;
}