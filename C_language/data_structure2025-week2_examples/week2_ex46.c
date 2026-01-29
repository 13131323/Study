/*
 * typedef
 */

#include <stdio.h>

// 구조체를 정의하면서 바로 typedef 키워드를 사용할 수 있다.
typedef struct _student_t {
    char *name;
    int studentid;
    double grade;
} student_t;

int main(void) {
    // 타입을 새롭게 재정의해도 이전 타입을 계속 사용할 수 있다. (단지 별명을 붙인 것일 뿐)
    struct _student_t chung_ang = {"Chung-Ang", 1916, 4.0};
    student_t puang = {"Puang", 20210000, 4.5};

    printf("size of chung_ang: %d\n", sizeof(chung_ang));
    printf("size of puang: %d\n", sizeof(puang));

    return 0;
}