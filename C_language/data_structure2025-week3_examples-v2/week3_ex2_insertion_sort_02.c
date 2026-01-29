/*
 * Insertion Sort #2 (매번 swap할 필요가 있나?)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef int element_t;      // 데이터의 타입을 재정의
#define FORMAT_SPEC "%d"    // 데이터의 출력 형식을 재정의

void insertion_sort(int *data, int n) {
    int i;   // 정렬할 데이터의 인덱스
    int j;   // 비교할 데이터의 인덱스
    int key; // 비교할 데이터를 저장할 변수

    for (i = 1; i < n; i++) {
        key = data[i];               // 삽입할 데이터를 key에 저장
        for (j = i; j >= 1 && data[j-1] > key; j--) // 적절한 위치를 찾을 때까지
            data[j] = data[j-1];     // 뒤로 이동
        data[j] = key;               // 삽입할 데이터를 삽입
    }
}

int main(int argc, char *argv[]) {
    char *fname;        // 파일 경로를 저장할 변수
    bool should_print;  // 배열을 출력할 것인지 여부를 저장할 변수

    clock_t start, end;

    FILE *fp;       // 파일포인터
    char line[256]; // 파일에서 읽은 한 줄을 저장할 문자열 버퍼
    int i;          // 반복문을 위한 변수

    element_t *myarr;   // 동적할당한 메모리를 포인팅할 변수
    element_t temp;     // 파일에서 읽은 데이터를 임시로 저장할 변수
    int capacity = 1;   // 동적할당한 메모리의 용량을 저장하는 변수  (배열의 용량)
    int cnt = 0;        // 실제로 읽은 데이터의 개수를 저장하는 변수 (저장된 데이터의 개수)

    // 명령행 인자가 부족하면 사용법 출력 후 종료
    if (argc < 3) {
        printf("Usage: %s <file_path> <print_option>\n", argv[0]);
        printf("    <file_path>: file path to read\n");
        printf("    <print_option>: 0(do not print), 1(print)\n");
        return 1;
    }
    fname = argv[1];        // 파일 경로를 저장
    
    switch(strtol(argv[2], NULL, 10))   // 2번째 인자를 정수로 변환한 값이
    {
        case 0: // 0이면 false
            should_print = false;
            break;
        case 1: // 1이면 true
            should_print = true;
            break;
        default:  // 0 또는 1이 아니면 종료
            printf("Invalid print option: %s\n", argv[2]);
            printf("    <print_option>: 0(do not print), 1(print)\n");
            return 1;
    }

    // 파일 열기
    fp = fopen(fname, "r");
    if (fp == NULL) {
        printf("Failed to open file: %s\n", fname);
        return 1;
    }

    capacity = 1;
    myarr = (element_t *)malloc(sizeof(element_t) * capacity);
    if (myarr == NULL) {
        printf("Failed to allocate memory!\n");
        fclose(fp); // 이 시점에는 파일 열기에는 성공한 상태이므로 파일을 닫아야함.
        return 1;
    }

    // 파일 읽기
    while (1) {
        if (fgets(line, sizeof(line), fp) == NULL) break; // 파일의 끝에 도달하면 종료
        if (line[0] == '\n' || strlen(line) == 0) continue; // 빈 줄이거나 개행문자만 있으면 다음 줄로
        if (sscanf(line, FORMAT_SPEC, &temp) != 1) break; // 읽기에 실패하면 종료
        
        myarr[cnt++] = temp; // 읽은 데이터를 배열에 저장 후 개수 증가
        if (cnt >= capacity) { // 용량이 다 차면 용량을 1칸 늘림
            capacity++;
            myarr = (element_t *)realloc(myarr, sizeof(element_t) * capacity);
            // realloc 실패 시 종료
            if (myarr == NULL) {
                printf("Failed to reallocate memory!\n");
                fclose(fp);
                return 1;
            }
        }
    }
    // 파일 닫기
    fclose(fp);
    
/******** 정렬 여부 확인 ********/
    // insertion sort 수행
    start = clock();
    insertion_sort(myarr, cnt);
    end = clock();

    if (should_print) {
        for (i = 0; i < cnt; i++)
            printf(FORMAT_SPEC " ", myarr[i]);
        printf("\n");
    }

    // 오름차순 여부 확인
    for (i = 0; i < cnt - 1; i++)
        if (myarr[i] > myarr[i + 1]) break;
    // for문이 끝까지 돌았으면 정렬된 상태
    if (i == cnt - 1) printf("Sorted!\n");
    else              printf("Not sorted!\n");
/********************************/

    // 수행시간 출력
    printf("Elapsed time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // 메모리 해제 (잊지말자 free!)
    free(myarr);

    return 0;
}