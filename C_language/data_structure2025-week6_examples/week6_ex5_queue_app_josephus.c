#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "queue_arr.h"
#include "element.h"

/** 자료구조 수업과는 큰 관련은 없습니다. 운영체제 별로 특정 시간동안 멈추는 함수가 달라 매크로상수와 함수로 정의하는 것입니다. **/
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

void print_queue(arr_queue_t *queue);

int main(int argc, char *argv[]) {
    // Command line argument 확인
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <k>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    if (n <= 0 || k <= 0) {
        printf("n and k must be positive integers.\n");
        return 1;
    }
    if (n < k) {
        printf("n must be greater than or equal to k.\n");
        return 1;
    }

    arr_queue_t *queue = NULL;
    if (!arr_queue_create(&queue)) {
        printf("Failed to create queue.\n");
        return 1;
    }

    // 초기 데이터 삽입 (1번부터 n번까지)
    for (int i = 0; i < n; i++) {
        element_t e;
        set_element(e, i+1); // 데이터 설정
        arr_queue_enqueue(queue, e); // 큐에 데이터 삽입
    }

    printf("Initial queue:\n");
    print_queue(queue); // 초기 큐 출력

    // 조세푸스 문제 해결
    int count = 0; // 카운트 변수
    while (arr_queue_get_size(queue) > 1) {
        element_t e;
        arr_queue_dequeue(queue, &e); // 맨 앞 데이터 삭제
        count++; // 카운트 증가

        if (count%k == 0) { // k의 배수 원소인 경우
            printf("Removed: ");
            print_element(e); // 삭제된 데이터 출력
            printf("\n");
        } else { // k번째 원소가 아닌 경우
            arr_queue_enqueue(queue, e); // 큐에 다시 삽입
        }
        print_queue(queue); // 현재 큐 출력
    }


    return 0;
}

// 큐의 모든 원소를 출력하는 함수
void print_queue(arr_queue_t *queue) {
    if (queue == NULL) {
        printf("Queue is NULL.\n");
        return;
    }
    if (arr_queue_is_empty(queue))
        return;

    int size = arr_queue_get_size(queue); // 큐의 크기
    printf("-");
    for (int i = 0; i < size; i++) {
        printf("----");
    }
    printf("-\n");

    printf(" ");
    element_t e;
    for (int i = 0; i < size-1; i++) {
        arr_queue_dequeue(queue, &e); // 큐에서 데이터 삭제
        print_element(e); // 데이터 출력
        printf(",");
        arr_queue_enqueue(queue, e); // 큐에 다시 삽입
    }
    arr_queue_dequeue(queue, &e); // 큐에서 데이터 삭제
    print_element(e); // 데이터 출력
    printf("\n");
    arr_queue_enqueue(queue, e); // 큐에 다시 삽입
    
    printf("-");
    for (int i = 0; i < size; i++) {
        printf("----");
    }
    printf("-\n");
    my_sleep(1); // 1초 대기
}