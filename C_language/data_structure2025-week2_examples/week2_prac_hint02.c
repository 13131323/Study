/*
 * Command line argument를 확인하여 데이터의 유효성을 검증하는 방법
 */

#include <stdio.h>
#include <string.h>

// argc는 argument의 개수, argv는 argument의 배열
int main(int argc, char *argv[]) {
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
    printf("All arguments are valid!\n");
    printf("File path: %s\n", fpath);
    printf("Subject: %s\n", subject);

    return 0;
}