/*
 * 메모리 관련 함수 (calloc)
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int i;
    int *malloc_p = (int *)malloc(5 * sizeof(int)); // int형 데이터를 5개 저장할 수 있는 동적 메모리를 할당받아 p에 대입
    int *calloc_p = (int *)calloc(5,  sizeof(int)); // int형 데이터를 5개 저장할 수 있는 동적 메모리를 할당받아 p에 대입

    // malloc은 할당받은 메모리의 값이 초기화되지 않는다.
    for (i = 0; i < 5; i++)
        printf("malloc_p[%d]: %d\n", i, malloc_p[i]);

    // calloc은 할당받은 메모리의 값이 0으로 초기화된다.
    for (i = 0; i < 5; i++)
        printf("calloc_p[%d]: %d\n", i, calloc_p[i]);

    // 잊지말자 free!!
    free(malloc_p);
    free(calloc_p);

    return 0;
}
