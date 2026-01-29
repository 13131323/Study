/*
 * 포인터 배열의 활용
 */


#include <stdio.h>

int main(void) {
    int i;
    // 배열 선언
    int arr1[3] = { 0x30, 0x44, 0x67 };
    int arr2[3] = { 0x87, 0x43 };

    // 배열의 이름은 시작 원소의 주소, 따라서 포인터 변수에 할당 가능
    int *p1 = arr1;
    int *p2 = arr2;

    // 포인터배열은 포인터 변수들의 배열
    int *p_arr[2] = { p1, p2 };

    // p_arr[0]은? p1의 값 == arr1의 시작주소
    printf("p_arr[0]:%p, p1:%p, arr1:%p\n", p_arr[0], p1, arr1);

    // p_arr[0][i]는? p1에 쓰여진 주소에서 i번째 원소의 값 == arr1[i]
    for (i = 0; i < 3; i++)
        printf("p_arr[0][%d]:%x, p1[%d]:%x, arr1[%d]:%x\n", i, p_arr[0][i], i, p1[i], i, arr1[i]);

    // p_arr[1]은? p2의 값 == arr2의 시작주소
    printf("p_arr[1]:%p, p2:%p, arr2:%p\n", p_arr[1], p2, arr2);

    // p_arr[1][i]는? p2에 쓰여진 주소에서 i번째 원소의 값 == arr2[i]
    for (i = 0; i < 3; i++)
        printf("p_arr[1][%d]:%x, p2[%d]:%x, arr2[%d]:%x\n", i, p_arr[1][i], i, p2[i], i, arr2[i]);
    
    return 0;
}