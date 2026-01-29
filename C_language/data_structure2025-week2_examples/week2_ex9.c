/*
 * 포인터 배열의 활용 #2
 */


#include <stdio.h>

int main(void) {
    int i;
    // 배열 선언
    int arr1[10000] = { 0x30, 0x44, 0x67 };
    int arr2[3] = { 0x87, 0x43 };

    int *arr3[2] = {arr1, arr2};
    int arr4[2][10000];

    /*
     배열의 이름은 시작 원소의 주소, 따라서 포인터 변수에 할당 가능
     따라서 포인터배열의 원소에 배열의 이름을 할당할 수 있다.
    */
    int *p_arr[2] = { arr1, arr2 };

    // p_arr[0]은? arr1의 시작주소
    printf("p_arr[0]:%p, arr1:%p\n", p_arr[0], arr1);

    // p_arr[0][i]는? p_arr[0] 쓰여진 주소(arr1)에서 i번째 원소의 값 == arr1[i]
    for (i = 0; i < 3; i++)
        printf("p_arr[0][%d]:%x, arr1[%d]:%x\n", i, p_arr[0][i], i, arr1[i]);

    // p_arr[1]은? arr2의 시작주소
    printf("p_arr[1]:%p, arr2:%p\n", p_arr[1], arr2);

    // p_arr[1][i]는? p_arr[1] 쓰여진 주소(arr2)에서 i번째 원소의 값 == arr2[i]
    for (i = 0; i < 3; i++)
        printf("p_arr[1][%d]:%x, arr2[%d]:%x\n", i, p_arr[1][i], i, arr2[i]);
    
    return 0;
}