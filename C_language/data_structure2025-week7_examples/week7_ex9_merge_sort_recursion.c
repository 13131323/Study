/*
 * Merge Sort를 재귀함수로 구현하는 방법
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

    merge_sort(arr, n); // 병합 정렬 수행

    printf("======== After sort ========\n");
    print_array(arr, n); // 정렬 후 배열 출력
    printf("\n");


    return 0;
}

void merge_sort(element_t *arr, int size) {
    if (size <= 1) return; // 배열 크기가 1 이하인 경우 정렬할 필요 없음

    // 누군가가 왼쪽 절반을 정렬해주고
    merge_sort(arr, size / 2);
    // 또 다른 누군가가 나머지 절반을 정렬해주면
    merge_sort(arr + size / 2, size - size / 2);

    // 나는 그걸 합치기만 하면 돼
    merge(arr, size / 2, size);
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

void print_array(element_t *arr, int size) {
    printf("[");
    for (int i = 0; i < size-1; i++) {
        printf("%d,  ", arr[i]); // 정렬 전 배열 출력
    }
    printf("%d", arr[size-1]); // 마지막 원소 출력
    printf("] "); // 배열 끝
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