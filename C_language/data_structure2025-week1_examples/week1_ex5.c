/*
 * swap 함수 예제 #1
 */

#include <stdio.h>

void swap(int a, int b) {   // 함수의 값 전달은 그냥 단순히 값을 복사하는 것
    int temp;
    temp = a;
    a = b;
    b = temp;
    // 따라서 원래의 값은 변하지 않는다.
}

int main(void) {
    int var1 = 10; int var2 = 20;
    printf("=== before ===\n");
    printf("var1:%d, var2:%d\n", var1, var2);
    swap(var1, var2);   // 주소가 아닌 값을 전달
    printf("=== after ===\n");
    printf("var1:%d, var2:%d\n", var1, var2);
    return 0;
}