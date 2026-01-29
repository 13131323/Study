/*
 * 배열 vs 포인터 #1
 */

#include <stdio.h>

int main(void) {
    int array[5] = { 22, 11, 26, 12, 23 };
    int *arr_p = &array[0];     // 배열의 시작(0번째) 값의 주소를 할당
    int i;

    // 배열의 인덱스로 접근
    printf("======= array[i] =======\n");
    for (i = 0; i < 5; i++)
        printf("  array[%d]:%d\n", i, array[i]);

    // 포인터의 연산으로 접근
    printf("===== *(arr_p + i) =====\n");
    for (i = 0; i < 5; i++)
        printf("*(arr_p+%d):%d\n", i, *(arr_p + i));

    // 증감연산자도 가능
    printf("====== *(arr_p++) ======\n");
    for (i = 0; i < 5; i++)
        printf("*(arr_p++):%d\n", *(arr_p++));

    return 0;
}