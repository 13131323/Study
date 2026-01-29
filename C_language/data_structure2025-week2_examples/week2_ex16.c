/*
 * C언어 버전에 따른 가변길이배열(VLA) 지원 여부
 */

#include <stdio.h>

/* C90이전 버전은 // 스타일의 한 줄 주석도 지원을 하지 않는다...  */
int main() {
    int N;
    scanf("%d", &N);
    int arr1[N]; /* 배열선언시 그 크기로 변수를 사용하면? */

    /* 해당 C언어 표준을 준수하는지 엄격히 확인하기 위해서는 -pedantic-errors 옵션을 사용한다. */
    /* ex) gcc -o run.exe source.c -std=c89 -pedantic-errors*/
    /*     --> source.c 파일을 run.exe 파일로 컴파일하며, c89 표준으로 컴파일하고 문법을 엄격히 확인 */
    return 0;
}