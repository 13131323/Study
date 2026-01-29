/*
 * 구조체 포인터
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

    // puang변수에서, name의 첫 글자에 접근하는 방법은?
    printf("The first letter of name of puang: %c\n", puang.name[0]);
    // 1차원배열 <-> 포인터의 관계를 이용하여 name의 첫 글자에 접근하는 방법은?
    printf("The first letter of name of puang: %c\n", *puang.name);

    // 구조체 포인터에서, name의 첫 글자에 접근하는 방법은?
    printf("The first letter of name of puang: %c\n", (*p).name[0]);
    // 1차원배열 <-> 포인터의 관계를 이용하여 name의 첫 글자에 접근하는 방법은?
    printf("The first letter of name of puang: %c\n", *(*p).name);

    // 멤버접근(.) <-> 포인터주소접근(*)의 순서가 있다. 보통 멤버접근이 더 높은 우선순위를 가진다.
    // 따라서 *p.name은? *(p.name)과 같다.



    return 0;
}