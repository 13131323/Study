/*
 * 동적메모리 할당 (malloc & free) #2
 * free를 사용하는 예제
*/

#include <stdio.h>
#include <stdlib.h>  // malloc, free 함수를 사용하기 위해 stdlib.h 헤더파일을 포함

void allocate_memory(void) {
    void *arr = malloc(10000); // 10KB 크기 동적메모리 할당
    free(arr); // 동적메모리 해제(반환)
}

int main(void) {
    int i = 0;
    while (1) {
        printf("%dth loop\n", ++i);
        allocate_memory(); // 반복해서 함수를 호출
    }

/* 4바이트를 동적으로 할당
   받고, int형으로 사용 */

    return 0;
}