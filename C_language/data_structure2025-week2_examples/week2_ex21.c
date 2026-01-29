/*
 * 동적메모리 할당 (malloc & free) #1
 * 배열(스택메모리)의 메모리 할당과 해제
*/

#include <stdio.h>

void create_array(void) {
    char arr[10000]; // 약 10KB 크기를 가지는 배열을 생성
}

int main(void) {
    int i = 0;
    while (1) {
        printf("%dth loop\n", ++i);
        create_array(); // 반복해서 함수를 호출
    }

    return 0;
}