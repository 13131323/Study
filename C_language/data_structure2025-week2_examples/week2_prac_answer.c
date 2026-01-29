/*
 * Command line argument를 확인하여 데이터의 유효성을 검증하는 방법
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 학생 정보를 저장하기 위한 구조체
typedef struct _student_t {
    char name[11];
    double kor;
    double eng;
    double math;
} student_t;

// 가독성을 위해 함수의 뼈대만 선언 후 main 함수 아래에 구현해보자
student_t parse_student_data(char *line);       // 문자열을 학생 정보로 변환하는 함수
int is_valid_argument(int argc, char *argv[]);  // argument의 유효성을 검증하는 함수
int get_highest_student(student_t *students, int N, char *subject); // 가장 높은 점수를 가진 학생의 위치를 찾는 함수
double get_target_score(student_t students, char *subject); // 학생의 과목 점수를 가져오는 함수

int main(int argc, char *argv[]) {
    // argument의 유효성을 검증
    int is_valid = is_valid_argument(argc, argv); // 정상적인 경우는 0, 비정상적인 경우는 0이 아닌 값을
    if (is_valid) {    // is_valid가 0이 아닐 경우 종료
        return is_valid;
    }

    // 파일을 읽기 모드로 열기
    char *fpath = argv[1];
    FILE *fp = fopen(fpath, "r");

    char buf[256]; // 파일에서 읽은 값을 저장할 버퍼
    int  cnt = 0;  // 현재까지 읽은 학생의 후
    int  capacity = 1; // 현재 배열의 용량
    student_t *students = (student_t *)malloc(sizeof(student_t) * capacity);    // 초기배열 생성

    while (fgets(buf, sizeof(buf), fp) != NULL) {   // 파일에서 데이터를 읽으면 (NULL이 아니면)
        if (cnt >= capacity) { // 현재까지 읽은 데이터가 capacity(용량)를 채우면
            capacity++; // 용량(capacity)를 늘린 후
            students = (student_t *)realloc(students, capacity * sizeof(student_t)); // 메모리를 다시 할당
        }
        students[cnt++] = parse_student_data(buf); // 문자열을 학생 정보로 변환하여 저장 후 cnt 증가
    }
    // 파일을 닫아주자
    fclose(fp);

    // 가장 높은 점수를 가진 학생을 찾는 함수 호출
    char *subject = argv[2];
    int highest_idx = get_highest_student(students, cnt, subject);
    printf("The student who has the highest %s score in the file %s is %s(%.2lf)\n", subject, fpath, students[highest_idx].name, get_target_score(students[highest_idx], subject));

    /** 가독성을 위해 변수를 생성하여 할당하기도 한다. **/
    // double highest_score = get_target_score(students[highest_idx], subject);
    // char *highest_name = students[highest_idx].name;
    // printf("The student who has the highest %s score in the file %s is %s(%.2lf)\n", subject, fpath, highest_name, highest_score);

    // 잊지 말자 free!!
    free(students);

    return 0;
}

// 문자열을 학생 정보로 변환하는 함수
student_t parse_student_data(char *line) {
    student_t student;
    // 첫 토큰은(line에서 시작) 공백으로 분리(" "), 데이터는 name
    char *ptr = strtok(line, " ");
    strcpy(student.name, ptr);

    // 이어서(NULL) 다음 토큰은 공백으로 분리(" "), 데이터는 kor
    ptr = strtok(NULL, " ");
    student.kor = atof(ptr);

    // 이어서(NULL) 다음 토큰은 공백으로 분리(" "), 데이터는 eng
    ptr = strtok(NULL, " ");
    student.eng = atof(ptr);

    // 이어서(NULL) 다음 토큰은 공백으로 분리(" "), 데이터는 math
    ptr = strtok(NULL, " ");
    student.math = atof(ptr);

    return student;
}

// argument의 유효성을 검증하는 함수
int is_valid_argument(int argc, char *argv[]) {
    // 원하는 argment는 파일경로, 과목 2가지 + 프로그램이름까지 더하면 총 3개
    // argv[0]: 프로그램이름
    // argv[1]: 파일경로
    // argv[2]: 과목
    // 총 3개의 인자를 받아야함.
    
    // 굳이 변수로 저장하지 않고 바로 사용해도 된지만, 가독성을 위해 변수로 저장해보자.
    char *program_name; char *fpath; char *subject;

    // 3개 미만의 argument가 들어오면 사용법을 출력하고 종료
    program_name = argv[0]; // 프로그램 이름은 argv[0]에 저장되어있다.
    if (argc < 3) {
        printf("Usage: %s [fpath] [subject]\n", program_name);
        return 1;
    }

    // 3개 이상의 argument가 들어왔으니 메모리에 접근해도 된다.
    fpath   = argv[1];
    subject = argv[2];

    // 파일이 존재하는지 확인
    FILE *fp = fopen(fpath, "r");
    if (fp == NULL) {
        printf("Cannot open the file %s\n", fpath);
        return 2;
    }
    // 파일을 열었으면 닫아주자.
    fclose(fp);

    // 과목이 올바른지 확인
    if (strcmp(subject, "kor")   != 0 && 
        strcmp(subject, "eng")   != 0 &&
        strcmp(subject, "math")  != 0 &&
        strcmp(subject, "total") != 0) {
            printf("Invalid subject %s\n", subject);
            return 3;
    }

    // 이 문장에 도달했다면 모든 argument가 유효하다.
    return 0;
}

// 가장 높은 점수를 가진 학생의 위치를 찾는 함수
int get_highest_student(student_t *students, int N, char *subject) {
    int i, highest_idx;
    double highest_score;

    // 가장 첫 학생을 최고점으로 가정
    highest_idx = 0;

    // 이후 학생부터 비교해보며 탐색
    for (i = 1; i < N; i++) {
        // 현재까지 최고점과 비교
        if (get_target_score(students[i], subject) > get_target_score(students[highest_idx], subject)) {
            highest_idx = i;
        }
    }
    return highest_idx;
}

// 학생의 과목 점수를 가져오는 함수
double get_target_score(student_t students, char *subject) {
    if (strcmp(subject, "kor") == 0) {
        return students.kor;
    } else if (strcmp(subject, "eng") == 0) {
        return students.eng;
    } else if (strcmp(subject, "math") == 0) {
        return students.math;
    } else if (strcmp(subject, "total") == 0) {
        return students.kor + students.eng + students.math;
    }
    return -1;  // argument의 유효성을 검증했다면 해당 문장은 실행되지 않을테지만...
}