/*
 * 배열 vs 구조체
 */

#include <stdio.h>

// 구조체의 멤버는 각기 다른 자료형을 가질 수 있다.
struct student {
    char name[6];
    int studentid;
    double grade;
};

int main(void) {
    // 배열과 구조체 모두 중괄호로 초기화
    struct student puang = {"Puang", 20210000, 4.5};    // 구조체의 멤버는 각기 다른 자료형을 가질 수 있다.
    double grades[4] = {4.5, 4.0, 3.5, 4.0};            // 배열의 원소는 모두 동일한 자료형으로 고정된다.
    double grades2[10] = {0};   // 배열은 생성할 때마다 크기를 지정할 수 있으나, 구조체는 한번 정의하면 크기를 바꿀 수 없다.
    
    int i;
    // 배열의 원소들은 서로 연속된 메모리에 저장된다.
    for (i = 0; i < 4; i++) {
        printf("Address of grades[%d]:       %p(in decimal: %d)\n", i, &grades[i], &grades[i]);
    }
    printf("sizeof array: %d\n", sizeof(grades));

    // 구조체의 멤버들은 서로 연속된 메모리에 저장되지 않을 수 있다.
    printf("\n\n");
    printf("Address of puang.name:      %p(in decimal: %d)\n", puang.name, puang.name);
    printf("Address of puang.studentid: %p(in decimal: %d)\n", &puang.studentid, &puang.studentid);
    printf("Address of puang.grade:     %p(in decimal: %d)\n", &puang.grade, &puang.grade);
    printf("sizeof struct: %d\n", sizeof(puang));

    return 0;
}