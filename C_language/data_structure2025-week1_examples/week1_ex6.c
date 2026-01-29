/*
 * swap 함수 예제 #2
 */

#include <stdio.h>

// 주소의 값을 받아온다.
void swap(int *a, int *b) {
    int temp;
    temp = *a;  // a변수에 담겨있는 주소로 "이동"하여 값을 가져온다.
    *a = *b;    // b변수에 담겨있는 주소로 "이동"하여 값을 가져온 후, a변수에 담겨있는 주소로 "이동"하여 값을 변경한다.
    *b = temp;  // temp변수에 담겨있는 값을 b변수에 담겨있는 주소로 "이동"하여 값을 변경한다.
}

int main(void) {
    int var1 = 10; int var2 = 20;
    printf("=== before ===\n");
    printf("var1:%d, var2:%d\n", var1, var2);
    swap(&var1, &var2);     // 주소를 전달
    printf("=== after ===\n");
    printf("var1:%d, var2:%d\n", var1, var2);
    return 0;
}