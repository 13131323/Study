/*
 * Merge Sort
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int element_t;

void merge_sort(element_t *arr, int size);
void merge(element_t *arr, int mid, int len);

void print_array(element_t *arr, int size);
void shuffle(element_t *arr, int size);

int main(int argc, char **argv) {
    // Command line argument 확인
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("n must be positive integers.\n");
        return 1;
    }

    // 배열 생성 및 초기화
    element_t *arr = (element_t *)malloc(sizeof(element_t) * n);
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }
    for (int i = 0; i < n; i++) arr[i] = i;
    shuffle(arr, n); // 배열을 랜덤하게 섞음

    printf("======== Before sort ========\n");
    print_array(arr, n); // 정렬 전 배열 출력
    printf("\n");

    printf("======== Sorting ========\n");
    merge_sort(arr, n); // 병합 정렬 수행

    printf("======== After sort ========\n");
    print_array(arr, n); // 정렬 후 배열 출력
    printf("\n");


    return 0;
}

void merge_sort(element_t *arr, int size) {
    for (int n = 1; n <= size; n *= 2) {        // n개짜리 배열
        for (int i = 0; i < size; i += n*2) {   // 2개를 정렬
            int left  = i;          // 처음
            int mid   = i + n;      // 중간
            int right = i + n*2;    // 끝

            // 각 인덱스가 size를 초과하지 않도록 조정
            if (  mid > size)   mid = size;
            if (right > size) right = size;
            
            int mid_len = mid - left; // 왼쪽 배열의 길이
            int len = right - left; // 정렬할 총 배열의 길이
            merge(arr + left, mid_len, len); // 병합 정렬 수행

            print_array(arr + i, len);
        }
        printf("\n");
    }
}

void merge(element_t *arr, int mid, int len) {
    int i = 0, j = mid, k = 0;

    // 임시 배열 생성
    element_t *temp = malloc(sizeof(element_t) * len);
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }

    // 두 개의 배열을 비교하여 작은 값을 temp에 저장
    while (i < mid && j < len) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else                  temp[k++] = arr[j++];
    }

    // 남은 원소들 처리
    while (i < mid) temp[k++] = arr[i++];
    while (j < len) temp[k++] = arr[j++];

    // 정렬된 배열을 원래 배열에 복사
    memcpy(arr, temp, sizeof(element_t) * len);

    // 임시 배열 메모리 해제
    free(temp);
}


/* 자료구조 수업과는 큰 관련은 없습니다. */
#if defined(_WIN64) || defined(_WIN32)
#include <windows.h> // Windows에서는 windows.h 헤더 포함
#define my_sleep(x) Sleep(x * 1000) // Windows에서는 Sleep 함수 사용
#elif defined(__APPLE__) ||defined(__MACH__)
#include <unistd.h> // macOS에서는 unistd.h 헤더 포함
#define my_sleep(x) sleep(x) // macOS에서는 sleep 함수 사용
#elif defined(__linux__) || defined(__linux)
#include <unistd.h> // Linux에서는 unistd.h 헤더 포함
#define my_sleep(x) sleep(x) // Linux에서는 sleep 함수 사용
#elif defined(__unix__) || defined(__unix)
#include <unistd.h> // Unix에서는 unistd.h 헤더 포함
#define my_sleep(x) sleep(x) // Unix에서는 sleep 함수 사용
#endif

void print_array(element_t *arr, int size) {
    printf("[");
    for (int i = 0; i < size-1; i++) {
        printf("%2d,  ", arr[i]); // 정렬 전 배열 출력
    }
    printf("%2d", arr[size-1]); // 마지막 원소 출력
    printf("] "); // 배열 끝
    my_sleep(1); // 잠깐 대기 (너무 빠르게 출력되면 보기 힘드니...)
}

// 랜덤하게 배열을 섞는 함수
void shuffle(element_t *arr, int size) {
    srand(0); // 랜덤 시드 초기화
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);  // 0 ~ i
        element_t temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}