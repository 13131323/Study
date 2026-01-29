/*
 * 구조체의 필요성
 */

#include <stdio.h>

int main(void) {
    // 학생의 정보를 저장하기 위한 변수들
    char name[] = "Puang";
    int year = 2021;
    char major[] = "Software";
    char address[] = "Incheon, Korea";
    double grade_programming = 4.5;
    double grade_oss_python  = 4.0;

    // 학생 한명을 더 추가하기 위해서는?
    char name2[] = "Chung-Ang";
    int year2 = 1916;
    char major2[] = "Software";
    char address2[] = "Seoul, Korea";
    double grade_programming2 = 4.0;
    double grade_oss_python2  = 3.5;

    // Puang의 주소는?
    printf("Address of Puang: %s\n", address);

    // Chung-Ang의 생년은?
    printf("Year of Chung-Ang: %d\n", year2);

    // Puang의 프로그래밍 성적은?
    printf("Programming grade of Puang: %.1f\n", grade_programming);

    // Chung-Ang의 OSS Python 성적은?
    printf("OSS Python grade of Chung-Ang: %.1f\n", grade_oss_python2);
    return 0;
}