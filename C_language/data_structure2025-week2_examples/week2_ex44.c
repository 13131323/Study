/*
 * 구조체 + 동적메모리 할당
 */

#include <stdio.h>
#include <stdlib.h>

struct student {
    char *name;
    int studentid;
    double grade;
};

int main(void) {
    struct student *students;
    int N;
    printf("input the number of students: ");
    scanf("%d", &N);
    students = (struct student *)malloc(sizeof(struct student) * N);

    // do something....

    // 잊지 말자 free!!
    free(students);

    return 0;
}