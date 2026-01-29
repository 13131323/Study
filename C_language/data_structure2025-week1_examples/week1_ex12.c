/*
 * 포인터의 연산 #1
 */

#include <stdio.h>

int main(void) {
    int array[10] = { 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 };
    int *arr_p = array;
    int i;

    // 포인터의 값에 상수를 더한 뒤 접근하면?
    arr_p = array;
    printf("==== adding -> pointing ====\n");
    for (i = 0; i < 10; i++)
        printf("%d\n", *(arr_p + i));

    // 포인터에 접근한 뒤 상수를 더하면?
    arr_p = array;
    printf("==== pointing -> adding ====\n");
    for (i = 0; i < 10; i++)
        printf("%d\n", (*arr_p) + i);

    return 0;
}