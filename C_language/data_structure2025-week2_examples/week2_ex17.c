/*
 * 메모리 저장 위치
*/

#include <stdio.h>

// 전역변수들
int global_var1;
short global_var2;
double global_var3;

// 함수들
void myfunc1(int p1, short p2, double p3) {
    printf("Hello World!! [myfunc1]\n");
}
void myfunc2(int *p1, short *p2, double *p3) {
    printf("Hello Programming!! [myfunc2]\n");
}

int main(void) {
    // 지역변수들
    int var1;
    short var2;
    double var3;
    int arr1[3];
    int i;

    // 지역변수(함수 내부에 존재하는 변수)의 메모리는 스택메모리에 할당
    // 선언된 순서대로 높은 주소부터 낮은 주소로 할당
    printf("====== memory of local variables ======\n");
    printf("var1: %p\n", &var1);
    printf("var2: %p\n", &var2);
    printf("var3: %p\n", &var3);
    printf("   i: %p\n", &i);
    printf("arr1: %p\n", arr1);
    for (i = 0; i < 3; i++) {
        printf("arr1[%d]: %p\n", i, &arr1[i]);
    }

    // 함수의 구현내용은 코드 -> Code segment(or Text segment)에 저장
    // 작성된 순서대로 가장 낮은 주소부터 할당
    printf("====== memory of functions ======\n");
    printf("myfunc1: %p\n", myfunc1);
    printf("myfunc2: %p\n", myfunc2);
    printf("   main: %p\n", main);

    // 전역의 메모리는 데이터 -> Data segment에 저장
    // 선언된 순서대로 낮은 주소부터 할당
    printf("====== memory of global variables ======\n");
    printf("global_var1: %p\n", &global_var1);
    printf("global_var2: %p\n", &global_var2);
    printf("global_var3: %p\n", &global_var3);

    return 0;
}