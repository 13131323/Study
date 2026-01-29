/*
 * 구조체의 정의와 초기화
 */

#include <stdio.h>

struct student {
    char name[20];
    int year;
    char major[20];
    char address[50];
    double grade_programming;
    double grade_oss_python;
};

int main(void) {
    // 구조체 변수를 초기화 할 때에는 멤버의 순서에 맞게 값을 넣어주어야 한다.
    struct student puang = {"Puang", 2021, "Software", "Incheon, Korea", 4.5, 4.0};

    // 학생 한명을 더 추가하기 위해서는?
    struct student chung_ang = {
        .year = 1916,           // 멤버의 이름을 명시적으로 지정할 수도 있다.
        .name = "Chung-Ang",    // 이 경우 순서가 바뀌어도 상관이 없다.
        .major = "Software",    // 또한 초기화하지 않은 멤버는 0으로 초기화된다.
        .address = "Seoul, Korea",
        .grade_oss_python = 3.5,
        .grade_programming = 4.0
    };

    // Puang의 주소는?
    printf("Address of Puang: %s\n", puang.address);

    // Chung-Ang의 생년은?
    printf("Year of Chung-Ang: %d\n", chung_ang.year);

    // Puang의 프로그래밍 성적은?
    printf("Programming grade of Puang: %.1f\n", puang.grade_programming);

    // Chung-Ang의 OSS Python 성적은?
    printf("OSS Python grade of Chung-Ang: %.1f\n", chung_ang.grade_oss_python);
    return 0;
}