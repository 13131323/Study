/*
 * 동적메모리 할당 + 형변환(type casting)
*/

#include <stdio.h>
#include <stdlib.h>  // malloc, free 함수를 사용하기 위해 stdlib.h 헤더파일을 포함


int main(void) {
    // 4바이트 크기 동적메모리 할당 후 int 포인터로 연결
    int *p = (int *)malloc(4);
    // -> p가 가리키는 곳으로 가서 int형으로 데이터를 다룰거야!

    // char 자료형의 크기(1바이트) 동적메모리 할당 후 char 포인터로 연결
    char *q = (char *)malloc(sizeof(char));
    // -> q가 가리키는 곳으로 가서 char형으로 데이터를 다룰거야!

    *p = 10;
    *q = 'A';

    printf("p: %p, *p: %d\n", p, *p);
    printf("q: %p, *q: %c\n", q, *q);

    // 잊지 말자 free!!
    free(p);
    free(q);

    return 0;
}