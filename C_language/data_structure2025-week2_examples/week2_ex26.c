/*
 * 동적메모리 할당 + 형변환(type casting)
 * N개의 원소를 가진 동적 배열 생성 예제
*/

#include <stdio.h>
#include <stdlib.h>  // malloc, free 함수를 사용하기 위해 stdlib.h 헤더파일을 포함


int main(void) {
    int *arr1;  // 동적메모리를 할당받을 포인터
    int N;      // 사용자에게 입력받을 배열의 크기
    int i;
    scanf("%d", &N);
    arr1 = (int *)malloc(N * sizeof(int)); // N개의 int형 원소를 가진 배열을 동적메모리로 할당

    // 배열처럼 사용
    for (i = 0; i < N; i++)
        arr1[i] = i * 10;

    // 출력도!
    for (i = 0; i < N; i++)
        printf("arr1[%d]: %d\n", i, arr1[i]);

    // 잊지 말자 free!!
    free(arr1);

    return 0;
}