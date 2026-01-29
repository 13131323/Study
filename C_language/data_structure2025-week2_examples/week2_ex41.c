/*
 * 구조체 포인터
 */

#include <stdio.h>

struct student {
    char name[20];
    int studentid;
    double grade;
};

int main(void) {
    struct student puang = {"Puang", 20210000, 4.5};

    struct student *p;

    p = &puang;
    printf("Name: %s\n", (*p).name);    // 포인터의 접근을 우선하기 위해서 괄호를 사용
    printf("Student ID: %d\n", (*p).studentid);
    printf("Grade: %.1f\n", (*p).grade);
    printf("Size of p: %d\n\n", sizeof(p)); // 포인터에 담기는 값은?? 그 크기는??

    return 0;
}