/*
 * 포인터의 연산 #2
 */

#include <stdio.h>

int main(void) {
    int array[10] = { 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 };
    int *arr_p = array;
    int i;

    // 증감연산자가 괄호 안에 있으면?
    arr_p = array;
    printf("==== increasing and then pointing ====\n");
    for (i = 0; i < 10; i++)
        printf("%d\n", *(arr_p++));

    // 증감연산자가 괄호 밖에 있으면?
    arr_p = array;
    printf("==== pointing and then increasing ====\n");
    for (i = 0; i < 10; i++)
        printf("%d\n", (*arr_p)++);

    // 다시 한 번, 증감연산자가 괄호 안에 있으면?
    arr_p = array;
    printf("==== increasing and then pointing ====\n");
    for (i = 0; i < 10; i++)
        printf("%d\n", *(arr_p++));

    return 0;
}