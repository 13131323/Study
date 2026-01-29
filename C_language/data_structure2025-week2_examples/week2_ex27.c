/*
 * 2차원 동적 메모리 할당
*/

#include <stdio.h>
#include <stdlib.h>  // malloc, free 함수를 사용하기 위해 stdlib.h 헤더파일을 포함
#include <string.h>  // strcpy 함수를 사용하기 위해 string.h 헤더파일을 포함

int main(void) {
    char **arr2d;  // 2차원 동적메모리를 할당받을 포인터
    int i;

    arr2d = (char **)malloc(3 * sizeof(char *));    // 3개의 문자배열을 가리킬 수 있는 포인터를 동적메모리로 할당
    arr2d[0] = (char *)malloc(12 * sizeof(char));   // 첫 번째 원소에 12바이트 크기의 문자배열을 동적메모리로 할당 (11글자의 문자열)
    strcpy(arr2d[0], "Programming");                // 문자열 복사(값 대입)
    arr2d[1] = (char *)malloc(6 * sizeof(char));    // 두 번째 원소에 6바이트 크기의 문자배열을 동적메모리로 할당 (11글자의 문자열)
    strcpy(arr2d[1], "Hello");                      // 문자열 복사(값 대입)
    arr2d[2] = (char *)malloc(7 * sizeof(char));    // 세 번째 원소에 7바이트 크기의 문자배열을 동적메모리로 할당 (11글자의 문자열)
    strcpy(arr2d[2], "World!");                      // 문자열 복사(값 대입)

    for (i = 0; i < 3; i++)
        printf("arr2d[%d]: %s\n", i, arr2d[i]);

    // 잊지말자 free!!
    free(arr2d);

    return 0;
}