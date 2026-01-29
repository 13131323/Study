/*
 * 배열의 크기 vs 포인터의 크기
 */

#include <stdio.h>

int main(void) {
    int array[5] = { 22, 11, 26, 12, 23 };
    int *arr_p = array;
    int i;

    printf("sizeof(array): %d\n", sizeof(array));   // 20
    printf("sizeof(arr_p): %d\n", sizeof(arr_p));   // 8

    return 0;
}