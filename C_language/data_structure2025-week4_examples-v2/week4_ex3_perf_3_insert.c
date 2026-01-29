/*
 * Performance measurement: Insertion Sort 매우 작은 input 값도 측정할 수 있게?
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef int element_t;      // 데이터의 타입을 재정의
#define FORMAT_SPEC "%d"    // 데이터의 출력 형식을 재정의

// 수행시간 출력을 위한 함수(자료구조 수업과는 큰 관련은 없습니다.)
void print_elapsed_time(int n, double elapsed, int repeat);

void insertion_sort(int *data, int n) {
    int i;   // 정렬할 데이터의 인덱스
    int j;   // 비교할 데이터의 인덱스
    int key; // 비교할 데이터를 저장할 변수

    for (i = 1; i < n; i++) {
        key = data[i];                    // 삽입할 데이터를 key에 저장
        for (j = i; j >= 1 && data[j-1] > key; j--) // 적절한 위치를 찾을 때까지 j를 이동하며
        {}                                          // 아무 작업도 하지 않음
        /** 이 시점에 j는 key가 들어갈 위치를 가리키고 있음 **/
        memmove(data + j + 1, data + j, sizeof(int) * (i - j)); // 한 번에 밀어내기
        data[j] = key;                                          // 삽입할 데이터를 삽입
    }
}

int main(int argc, char *argv[]) {
    char *fname;        // 파일 경로를 저장할 변수

    FILE *fp;       // 파일포인터
    char line[256]; // 파일에서 읽은 한 줄을 저장할 문자열 버퍼
    int i;          // 반복문을 위한 변수

    element_t *myarr;   // 동적할당한 메모리를 포인팅할 변수
    element_t temp;     // 파일에서 읽은 데이터를 임시로 저장할 변수
    int capacity = 1;   // 동적할당한 메모리의 용량을 저장하는 변수  (배열의 용량)
    int cnt = 0;        // 실제로 읽은 데이터의 개수를 저장하는 변수 (저장된 데이터의 개수)

    clock_t start, end; // 시간 측정을 위한 변수

    // 명령행 인자가 부족하면 사용법 출력 후 종료
    if (argc < 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        printf("    <file_path>: file path to read\n");
        return 1;
    }
    fname = argv[1];        // 파일 경로를 저장

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

/**** 2배씩 늘려가며 시간 측정 ****/
    // insertion sort 수행 (insertion sort에서 그 뒤는 너무 오래걸리니까 2^17까지)
    for (i = 250; i <= cnt && i <= (1<<17); i *= 2) {
        start = clock();
        int repeat = 0;
        double elapsed = 0.0;
        while (1) {
            insertion_sort(myarr, i);
            repeat++;
            end = clock();
            elapsed = (double)(end - start) / CLOCKS_PER_SEC;
            if (elapsed > 1.0) break; // 1초가 넘으면 종료
        }
        // 1초가 넘는 시간이 될 때까지, 계속 반복하고 그 평균을 출력
        double avg = elapsed / repeat;
        print_elapsed_time(i, avg, repeat);
    }
/********************************/

    // 메모리 해제 (잊지말자 free!)
    free(myarr);

    return 0;
}



// 수행시간 출력을 위한 함수(자료구조 수업과는 큰 관련은 없습니다.)
void print_elapsed_time_1(int n, double elapsed, int repeat) {
    static int cnt = 0;
    if (cnt++ == 0) {
        printf("****** N vs Running Time (in second) ******\n");
        printf("|    N   |   Time   | # Repeat |\n");
        printf("|--------|----------|----------|\n");
    }
    printf("| %6d | %8lf | %-8d |\n", n, elapsed, repeat);
    printf("|--------|----------|----------|\n");
}
/** 더 예쁘긴 한데 실행환경의 인코딩에 따라서 잘 안보일수도... */
void print_elapsed_time_2(int n, double elapsed, int repeat) {
    static int cnt = 0;
    if (cnt++ == 0) {
        printf("****** N vs Running Time (in second) ******\n");
        printf("┌────────┬──────────┬──────────┐\n");
        printf("│    N   │   Time   │ # Repeat │\n");
        printf("├────────┼──────────┼──────────┤\n");
    }
    printf("│ %6d │ %8lf │ %-8d │\n", n, elapsed, repeat);
    if (cnt == 10) {
        printf("└────────┴──────────┴──────────┘\n");
    }
    else {
        printf("├────────┼──────────┼──────────┤\n");
    }
}
void print_elapsed_time(int n, double elapsed, int repeat) {
    print_elapsed_time_1(n, elapsed, repeat);
    // print_elapsed_time_2(n, elapsed, repeat);
}