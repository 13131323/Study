/*
 * 문자열을 학생 정보로 변환하는 방법 (데이터가 공백/띄어쓰기로 구분되어있을 때)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _student_t {
    char name[11];
    double kor;
    double eng;
    double math;
};

// 방법 01: sscanf 함수를 이용한 방법
struct _student_t line_to_student01(char *line) {
    struct _student_t student;
    sscanf(line, "%s %lf %lf %lf", student.name, &student.kor, &student.eng, &student.math);
    return student;
}

// 방법 02: strtok 함수를 이용한 방법
struct _student_t line_to_student02(char *line) {
    struct _student_t student;
    // 첫 토큰은(line에서 시작) 공백으로 분리(" "), 데이터는 name
    char *ptr = strtok(line, " ");
    strcpy(student.name, ptr);

    // 이어서(NULL) 다음 토큰은 공백으로 분리(" "), 데이터는 kor
    ptr = strtok(NULL, " ");
    student.kor = atof(ptr);
    // student.kor = strtod(ptr, NULL); // 또는 strtod 함수를 사용할 수도 있다.

    // 이어서(NULL) 다음 토큰은 공백으로 분리(" "), 데이터는 eng
    ptr = strtok(NULL, " ");
    student.eng = atof(ptr);
    // student.eng = strtod(ptr, NULL); // 또는 strtod 함수를 사용할 수도 있다.

    // 이어서(NULL) 다음 토큰은 공백으로 분리(" "), 데이터는 math
    ptr = strtok(NULL, " ");
    student.math = atof(ptr);
    // student.math = strtod(ptr, NULL); // 또는 strtod 함수를 사용할 수도 있다.
    
    return student;
}

int main(void) {
    char line[] = "Puang 100 90 80";
    char line2[] = "Chung-Ang 90 80 70";
    struct _student_t student01 = line_to_student01(line);
    struct _student_t student02 = line_to_student02(line2);

    printf("name: %s, kor: %.1f, eng: %.1f, math: %.1f\n", student01.name, student01.kor, student01.eng, student01.math);
    printf("name: %s, kor: %.1f, eng: %.1f, math: %.1f\n", student02.name, student02.kor, student02.eng, student02.math);

    return 0;
}