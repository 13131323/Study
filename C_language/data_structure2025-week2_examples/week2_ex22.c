/*
 * 동적메모리 할당 (malloc & free) #2
 * free를 사용하지 않아 메모리 누수가 발생하는 예제
*/

#include <stdio.h>
#include <stdlib.h>  // malloc, free 함수를 사용하기 위해 stdlib.h 헤더파일을 포함

/* !!!!!!!!!!!!!!!!!!!!주의!!!!!!!!!!!!!!!!!!!! */
/* free를 사용하지 않아 메모리 누수가 발생하는 예제입니다.
   너무 오래 실행하면 메모리가 부족해져서 컴퓨터가 멈출 수 있으니
   적당히 메모리 누수가 발생하는 것을 확인하고 종료하시기 바랍니다.
   터미널 창에서 실행 중인 프로그램을 강제로 종료(Ctrl + C)하거나,
   터미널을 강제로 종료하거나,
   Visual Studio Code를 강제종료하시기 바랍니다. */
void allocate_memory(void) {
    void *arr = malloc(10000); // 10KB 크기 동적메모리 할당
}

int main(void) {
    int i = 0;
    while (1) {
        printf("%dth loop\n", ++i);
        allocate_memory(); // 반복해서 함수를 호출
    }

    return 0;
}