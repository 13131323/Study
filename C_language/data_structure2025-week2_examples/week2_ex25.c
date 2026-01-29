/*
 * 동적메모리 할당 + 형변환(type casting)
 * 동적 배열 생성 예제
*/

#include <stdio.h>
#include <stdlib.h>  // malloc, free 함수를 사용하기 위해 stdlib.h 헤더파일을 포함


int main(void) {
    int i;
    int *p = (int *)malloc(40); // 40바이트 크기 동적메모리 할당 후 int 포인터로 연결

    printf("p: %p\n", p);       // p는 할당받은 메모리의 "시작주소"를 가리킴
    printf("p+1: %p\n", p+1);   // p+1은 할당받은 메모리의 "시작주소"에서 한칸 뒤(+4바이트(int))를 가리킴
    // 배열과 유사하네?

    *p = 10;    // p가 가리키는 곳에 10을 저장
    *(p+1) = 20;    // p가 가리키는 곳에서 한칸 뒤(+4바이트)에 20을 저장
    printf("*p: %d *(p+1): %d\n", *p, *(p+1));
    // 포인터때 배웠던거네?

    // 포인터 <-> 배열의 관계를 떠올려서...
    p[2] = 30;
    p[3] = 40;
    printf("p[2]: %d p[3]: %d\n", p[2], p[3]);

    // 그렇다면 배열처럼 사용하면 반복문을 통해 값을 초기화?
    for (i = 0; i < 10; i++)
        p[i] = i * 10;
    
    // 출력도!
    for (i = 0; i < 10; i++)
        printf("p[%d]: %d\n", i, p[i]);

    // 잊지 말자 free!!
    free(p);

    return 0;
}