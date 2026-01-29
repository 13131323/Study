/*
 * 스택메모리
*/

#include <stdio.h>

// 함수들
void myfunc1(int p1, short p2, double p3) {
    printf("--- [myfunc1] ---\n");
    printf("  p1: %p\n", &p1);
    printf("  p2: %p\n", &p2);
    printf("  p3: %p\n", &p3);
}
void myfunc2(int *p1, short *p2, double *p3) {
    int var1, var2, var3;
    printf("--- [myfunc2] ---\n");
    printf("  p1: %p\n", &p1);
    printf("  p2: %p\n", &p2);
    printf("  p3: %p\n", &p3);
    printf("var1: %p\n", &var1);
    printf("var2: %p\n", &var2);
    printf("var3: %p\n", &var3);
    myfunc1(*p1, *p2, *p3);
}

int main(void) {
    // 지역변수들
    int var1;
    short var2;
    double var3;

    // 지역변수(함수 내부에 존재하는 변수)의 메모리는 스택메모리에 할당
    // 선언된 순서대로 높은 주소부터 낮은 주소로 할당
    printf("====== memory of local variables ======\n");
    printf("var1: %p\n", &var1);
    printf("var2: %p\n", &var2);
    printf("var3: %p\n", &var3);

    // myfunc1을 호출하면?
    printf("Call myfunc1 in main\n");
    myfunc1(var1, var2, var3);
    /* main함수의 stack메모리에 이어서 myfunc1에 관련된 메모리가 적재되었다. */


    // myfunc2를 호출하면?
    printf("Call myfunc2 in main\n");
    myfunc2(&var1, &var2, &var3);
    /* myfunc1이 사용했던 메모리를 다시쓰고 있다. 그리고,
       main함수의 stack메모리에 이어서 myfunc2에 관련된 메모리가 적재된 이후 
       myfunc2함수의 stack메모리에 이어서 myfunc1이 호출되며 관련된 메모리가 적재된다.*/

    return 0;
}