/*
 * 구조체의 메모리
 */

#include <stdio.h>

// 2바이트 + 2바이트 + 4바이트
struct type_d {
    short d_short_1;
    short d_short_2;
    int   d_int_1;
};

// 2바이트 + 4바이트 + 8바이트
struct type_e {
    short  e_short_1;
    int    e_int_1;
    double e_double_1;
};

// 배열?
struct type_f {
    char   f_char_1[10];
    int    f_int_1;
    double f_double_1;
};

int main(void) {
    struct type_d d;
    struct type_e e;
    struct type_f f;

    // 수행결과는?
    printf("Address of d.d_short_1:  %p(in decimal: %d)\n", &d.d_short_1, &d.d_short_1);
    printf("Address of d.d_short_2:  %p(in decimal: %d)\n", &d.d_short_2, &d.d_short_2);
    printf("Address of d.d_int_1:    %p(in decimal: %d)\n", &d.d_int_1, &d.d_int_1);
    printf("sizeof d: %d\n\n", sizeof(d));

    // 수행결과는?
    printf("Address of e.e_short_1:  %p(in decimal: %d)\n", &e.e_short_1, &e.e_short_1);
    printf("Address of e.e_int_1:    %p(in decimal: %d)\n", &e.e_int_1, &e.e_int_1);
    printf("Address of e.e_double_1: %p(in decimal: %d)\n", &e.e_double_1, &e.e_double_1);
    printf("sizeof e: %d\n\n", sizeof(e));

    // 수행결과는?
    printf("Address of f.f_char_1:   %p(in decimal: %d)\n", f.f_char_1, f.f_char_1);
    printf("Address of f.f_int_1:    %p(in decimal: %d)\n", &f.f_int_1, &f.f_int_1);
    printf("Address of f.f_double_1: %p(in decimal: %d)\n", &f.f_double_1, &f.f_double_1);
    printf("sizeof f: %d\n\n", sizeof(f));

    return 0;
}