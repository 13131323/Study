/*
 * 가변길이 배열 (VLA: Variable Length Array)
 */

#include <stdio.h>

int main(void) {
    // 변수에 값을 할당하고 배열의 크기로 사용할 수 있다.
    int size = 10;
    int array1[size];
    // 배열의 길이는 배열의 총 바이트크기 / 배열의 한 요소의 바이트크기
    printf("size of array1: %ld\n", sizeof(array1) / sizeof(int));

    // 따라서 사용자로부터 입력을 받아서 배열의 크기를 지정할 수 있다.
    int N;
    printf("input the number of elements: ");
    scanf("%d", &N);
    int array2[N];
    printf("size of array2: %ld\n", sizeof(array2) / sizeof(int));

    return 0;
}