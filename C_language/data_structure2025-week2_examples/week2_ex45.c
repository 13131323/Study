/*
 * typedef
 */

#include <stdio.h>

struct student {
    char *name;
    int studentid;
    double grade;
};

// struct student 타입을 student로 재정의
typedef struct student student;
// unsigned long long int 타입을 ull로 재정의
typedef unsigned long long int ull;

int main(void) {
    // 타입을 새롭게 재정의해도 이전 타입을 계속 사용할 수 있다. (단지 별명을 붙인 것일 뿐)
    struct student chung_ang = {"Chung-Ang", 1916, 4.0};
    student puang = {"Puang", 20210000, 4.5};

    printf("size of chung_ang: %d\n", sizeof(chung_ang));
    printf("size of puang: %d\n", sizeof(puang));

    // 기본 자료형도 재정의가 가능하다.
    ull a = 1234;
    unsigned long long int b = 1234;

    printf("size of a: %d\n", sizeof(a));
    printf("size of b: %d\n", sizeof(b));

    return 0;
}