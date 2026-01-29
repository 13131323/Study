/*
 * 포인터 배열
 */


#include <stdio.h>

int main(void) {
    int i;
    // 여러 타입의 변수들
    int int_a = 9, int_b = 11, int_c = 12;  // int(4바이트 정수)형 변수들
    short short_a = 9, short_b = 11, short_c = 12; // short(2바이트 정수)형 변수들
    float float_a = 9.22, float_b = 11.26, float_c = 12.22; // float(4바이트 실수)형 변수들
    double double_a = 9.22, double_b = 11.26, double_c = 12.22; // double(8바이트 실수)형 변수들
    int *p_a = &int_a, *p_b = &int_b, *p_c = &int_c; // int형 포인터 변수들

    // 변수들을 연속된 메모리에 묶으면? --> 배열
    int int_arr[3] = { int_a, int_b, int_c };   // int 배열
    short short_arr[3] = { short_a, short_b, short_c }; // short 배열
    float float_arr[3] = { float_a, float_b, float_c }; // float 배열
    double double_arr[3] = { double_a, double_b, double_c }; // double 배열

    // 포인터 변수들을 연속된 메모리에 묶으면? --> 포인터 배열
    int *p_arr[3] = { p_a, p_b, p_c }; // int형 포인터 변수들의 배열, int 포인터 배열

    // int 배열
    printf("=== int_arr(%p) ===\n", int_arr);   // 배열의 이름은 배열의 시작주소
    for (i = 0; i < 3; i++) {
        printf("int_arr[%d]:%d (memory:%p)\n", i, int_arr[i], &int_arr[i]); // 각 원소의 값과 주소
    }

    // short 배열
    printf("=== short_arr(%p) ===\n", short_arr); // 배열의 이름은 배열의 시작주소
    for (i = 0; i < 3; i++) {
        printf("short_arr[%d]:%d (memory:%p)\n", i, short_arr[i], &short_arr[i]); // 각 원소의 값과 주소
    }

    // float 배열
    printf("=== float_arr(%p) ===\n", float_arr); // 배열의 이름은 배열의 시작주소
    for (i = 0; i < 3; i++) {
        printf("float_arr[%d]:%f (memory:%p)\n", i, float_arr[i], &float_arr[i]); // 각 원소의 값과 주소
    }

    // double 배열
    printf("=== double_arr(%p) ===\n", double_arr); // 배열의 이름은 배열의 시작주소
    for (i = 0; i < 3; i++) {
        printf("double_arr[%d]:%f (memory:%p)\n", i, double_arr[i], &double_arr[i]); // 각 원소의 값과 주소
    }

    // int 포인터 배열
    printf("=== p_arr(%p) ===\n", p_arr); // 배열의 이름은 배열의 시작주소
    for (i = 0; i < 3; i++) {
        printf("p_arr[%d]:%p (memory:%p)\n", i, p_arr[i], &p_arr[i]); // 각 원소의 값과 주소
    }
    
    return 0;
}