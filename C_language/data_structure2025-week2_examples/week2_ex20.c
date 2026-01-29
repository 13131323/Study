/*
 * 동적메모리 할당 (malloc)
*/

#include <stdio.h>
#include <stdlib.h> // 동적메모리 관리를 위한 함수는 stdlib.h에 선언되어 있다.

int global_var1;    // 전역변수

int main(void) {
    int var1, var2, var3;   // 지역변수
    void *p1;
    p1 = malloc(10000000);    // 10MB의 크기를 할당할 수 있는가?
    void *p2;
    p2 = malloc(10000000);    // p2에 다시 malloc을 통해 동적메모리 할당
    
    printf("%p:Code segment (main function)\n", main);
    printf("%p:Data segment\n", &global_var1);
    printf("%p:Stack segment (var1)\n", &var1);
    printf("%p:Stack segment (var2)\n", &var2);
    printf("%p:Stack segment (var3)\n", &var3);

    if (p1 == NULL) {    // malloc 함수는 할당에 실패하면 NULL을 반환
        printf("Failed to allocate memory (p1)!\n");
    } else {            // NULL이 아니면 할당을 받은 것
        printf("Success to allocate 10MB memory (p2)!\n");
        printf("%p:Stack segment (p1)\n", &p1);
        printf("%p:Heap segment (allocated memory (in p1))\n", p1);
    }

    if (p2 == NULL) {    // malloc 함수는 할당에 실패하면 NULL을 반환
        printf("Failed to allocate memory (p2)!\n");
    } else {            // NULL이 아니면 할당을 받은 것
        printf("Success to allocate 10MB memory (p2)!\n");
        printf("%p:Stack segment (p2)\n", &p2);
        printf("%p:Heap segment (allocated memory (in p2))\n", p2);
    }

    return 0;
}