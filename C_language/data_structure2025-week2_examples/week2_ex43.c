/*
 * 구조체 포인터의 접근 연산자
 */

#include <stdio.h>

struct student {
    char *name;
    int studentid;
    double grade;
};

int main(void) {
    struct student puang = {"Puang", 20210000, 4.5};

    struct student *p;

    p = &puang;
    printf("===== Access by pointer, and then access member =====\n");
    printf("Name: %s\n", (*p).name);    // 포인터의 접근을 우선하기 위해서 괄호를 사용
    printf("Student ID: %d\n", (*p).studentid);
    printf("Grade: %.1f\n", (*p).grade);

    // 포인터접근(*) 후 멤버접근(.)을 한 번에 수행할 수있다. 포인터의 멤버에 접근 (->)
    printf("===== Access member of pointer directly =====\n");
    printf("Name: %s\n", p->name);
    printf("Student ID: %d\n", p->studentid);
    printf("Grade: %.1f\n", p->grade);


    return 0;
}