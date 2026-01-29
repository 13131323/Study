/*
 * 포인터 변수의 산술 연산
 */

#include <stdio.h>

int main(void) {
    /*
      실제로 포인터 변수에 상수를 강제로 할당하는 것은 매우 위험하니,
      예제로만 이해하고 실전에서는 절!대!로! 하지 마세요.
    */ 
    int *p_int;
    short *p_short;

    printf("======= Integer pointer =======\n");
    p_int = (int *)1;   printf("p_int: %p\n", p_int);   // p_int: 1
    p_int = p_int + 1;  printf("p_int: %p\n", p_int);   // p_int: 5
    p_int = p_int + 1;  printf("p_int: %p\n", p_int);   // p_int: 9
    p_int = p_int - 1;  printf("p_int: %p\n", p_int);   // p_int: 5

    printf("======= Short pointer =======\n");
    p_short = (short *)1;   printf("p_short: %p\n", p_short); // p_short: 1
    p_short = p_short + 1;  printf("p_short: %p\n", p_short); // p_short: 3
    p_short = p_short + 1;  printf("p_short: %p\n", p_short); // p_short: 5
    p_short = p_short - 1;  printf("p_short: %p\n", p_short); // p_short: 3

    return 0;
}
