#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "stack_linked.h"
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
void print_towers(linked_stack_t *A, linked_stack_t *B, linked_stack_t *C, int n, int cnt);

void compare_and_move_disk(linked_stack_t *first, linked_stack_t *second);

int main(int argc, char *argv[]) {
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

    linked_stack_t *src, *aux, *dest; // 스택 선언
    if (!linked_stack_create(&src)) {
        printf("Failed to create stack A.\n");
        return 1;
    }
    if (!linked_stack_create(&aux)) {
        linked_stack_destroy(&src); // A 스택 해제
        printf("Failed to create stack B.\n");
        return 1;
    }
    if (!linked_stack_create(&dest)) {
        linked_stack_destroy(&src); // A 스택 해제
        linked_stack_destroy(&aux); // B 스택 해제
        printf("Failed to create stack C.\n");
        return 1;
    }

    // 스택 A에 원반 삽입
    for (int i = n; i >= 1; i--) {  // 큰 원반부터
        element_t e;
        set_element(e, i); // 데이터 설정
        linked_stack_push(src, e); // 스택 A에 원반 삽입
    }

    /**** 하노이 탑 문제 해결 ****/
    linked_stack_t *A_stack = src; // 출발 스택
    linked_stack_t *B_stack = NULL; // 목적지 스택
    linked_stack_t *C_stack = NULL; // 보조 스택
    if (n % 2 == 0) { // 짝수이면 B가 보조 스택
        B_stack = aux; // 보조 스택
        C_stack = dest; // 목적지 스택
    } else { // 홀수이면 B가 목적지 스택
        B_stack = dest; // 목적지 스택
        C_stack = aux; // 보조 스택
    }

    print_towers(src, aux, dest, n, 0); // 초기 상태 출력

    // 원반 이동
    // 목적지 노드의 원반 개수가 n이 될 때까지 반복
    int count = 1; // 이동 횟수
    while (linked_stack_get_size(dest) < n) {
        if (count % 3 == 1) // 1단계
            // A와 B 스택을 비교하여 이동
            compare_and_move_disk(A_stack, B_stack);
        else if (count % 3 == 2) // 2단계
            // A와 C 스택을 비교하여 이동
            compare_and_move_disk(A_stack, C_stack);
        else if (count % 3 == 0) // 3단계
            // B와 C 스택을 비교하여 이동
            compare_and_move_disk(B_stack, C_stack);
        print_towers(src, aux, dest, n, count); // 현재 상태 출력
        count++; // 이동 횟수 증가
    }

    return 0;
}

void compare_and_move_disk(linked_stack_t *first, linked_stack_t *second) {
    element_t e1, e2; // 임시로 사용할 데이터

    // 첫 번째 스택이 비어있으면
    if (linked_stack_is_empty(first)) {
        linked_stack_pop(second, &e2); // 두 번째 스택에서 원반 삭제
        linked_stack_push(first,  e2);  // 첫 번째 스택에 원반 삽입
        return;
    }

    // 두 번째 스택이 비어있으면
    if (linked_stack_is_empty(second)) {
        linked_stack_pop(first,  &e1); // 첫 번째 스택에서 원반 삭제
        linked_stack_push(second, e1); // 두 번째 스택에 원반 삽입
        return;
    }

    // 둘 다 비어있지 않으면 top 원반의 크기를 비교하여 작은쪽을 이동
    if (linked_stack_peek(first, &e1) && linked_stack_peek(second, &e2)) {
        if (e1.data < e2.data) { // 첫 번째 스택의 원반이 더 작으면
            linked_stack_pop(first, &e1); // 첫 번째 스택에서 원반 삭제
            linked_stack_push(second, e1); // 두 번째 스택에 원반 삽입
        } else { // 두 번째 스택의 원반이 더 작으면
            linked_stack_pop(second, &e2); // 두 번째 스택에서 원반 삭제
            linked_stack_push(first, e2);  // 첫 번째 스택에 원반 삽입
        }
    }
}

/***** 아래 코드부터는 자료구조 수업과는 큰 관련이 없습니다. *****/
void print_single_tower(int n, int l) {
    for (int j = 0; j < n-(l); j++) {
        printf(" ");
    }
    for (int j = 0; j < l*2-1; j++) {
        printf("-");
    }
    for (int j = 0; j < n-(l); j++) {
        printf(" ");
    }
}

void print_towers(linked_stack_t *A, linked_stack_t *B, linked_stack_t *C, int n, int cnt) {
    linked_stack_t *temp_A, *temp_B, *temp_C; // 임시 스택 선언

    if (!linked_stack_create(&temp_A)) {
        printf("Failed to create temporary stack A.\n");
        return;
    }
    if (!linked_stack_create(&temp_B)) {
        linked_stack_destroy(&temp_A); // 임시 스택 A 해제
        printf("Failed to create temporary stack B.\n");
        return;
    }
    if (!linked_stack_create(&temp_C)) {
        linked_stack_destroy(&temp_A); // 임시 스택 A 해제
        linked_stack_destroy(&temp_B); // 임시 스택 B 해제
        printf("Failed to create temporary stack C.\n");
        return;
    }
    printf("\n======================== %d ========================\n", cnt);
    for (int i = n + 1; i >= 1; i--) {
        if (linked_stack_get_size(A) == i) {
            element_t e;
            linked_stack_pop(A, &e); // 스택 A에서 원반 삭제
            linked_stack_push(temp_A, e); // 임시 스택 A에 삽입
            int l = e.data;
            print_single_tower(n, l); // 원반 출력
        }
        else {
            for (int j = 0; j < n-1; j++) printf(" ");
            printf("|");
            for (int j = 0; j < n-1; j++) printf(" ");
        }
        if (linked_stack_get_size(B) == i) {
            element_t e;
            linked_stack_pop(B, &e); // 스택 B에서 원반 삭제
            linked_stack_push(temp_B, e); // 임시 스택 B에 삽입
            int l = e.data;
            print_single_tower(n, l); // 원반 출력
        }
        else {
            for (int j = 0; j < n-1; j++) printf(" ");
            printf("|");
            for (int j = 0; j < n-1; j++) printf(" ");
        }
        if (linked_stack_get_size(C) == i) {
            element_t e;
            linked_stack_pop(C, &e); // 스택 C에서 원반 삭제
            linked_stack_push(temp_C, e); // 임시 스택 C에 삽입
            int l = e.data;
            print_single_tower(n, l); // 원반 출력
        }
        else {
            for (int j = 0; j < n-1; j++) printf(" ");
            printf("|");
            for (int j = 0; j < n-1; j++) printf(" ");
        }
        printf("\n");
    }
    printf("===================================================\n");
    while (linked_stack_is_empty(temp_A) != true) {
        element_t e;
        linked_stack_pop(temp_A, &e);
        linked_stack_push(A, e);
    }
    while (linked_stack_is_empty(temp_B) != true) {
        element_t e;
        linked_stack_pop(temp_B, &e);
        linked_stack_push(B, e);
    }
    while (linked_stack_is_empty(temp_C) != true) {
        element_t e;
        linked_stack_pop(temp_C, &e);
        linked_stack_push(C, e);
    }
    linked_stack_destroy(&temp_A); // 임시 스택 A 해제
    linked_stack_destroy(&temp_B); // 임시 스택 B 해제
    linked_stack_destroy(&temp_C); // 임시 스택 C 해제

    my_sleep(1); // 1초 대기
}