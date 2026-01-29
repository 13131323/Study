/*
 * Doubly Linked List
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "element.h"
#include "array_list.h"
#include "singly_linked_list.h"
#include "doubly_linked_list.h"

#define REPEAT_CNT 10000  // 반복 횟수
// 수행시간 출력을 위한 함수(자료구조 수업과는 큰 관련은 없습니다.)
void print_performance_comparison(char *func, double al_elapsed, double sll_elapsed, double dll_elapsed);
 
int main(int argc, char **argv) {
    array_list_t *myarrlist = NULL;    // arraylist 선언
    s_linked_list_t *mysllist = NULL;  // singly linked list 선언
    d_linked_list_t *mydllist = NULL; // doubly linked list 선언

    clock_t start, end;             // 시간 측정을 위한 변수
    double al_elapsed, sll_elapsed, dll_elapsed;  // Array List와 Linked List의 수행시간을 저장할 변수

    /**** 각 리스트 생성 ****/
    // arraylist 생성
    if (array_list_create(&myarrlist) == false) {
        printf(" Array List: Failed to create array list!\n");
        return 1;
    }
    // singly linked list 생성
    if (s_linked_list_create(&mysllist) == false) {
        printf("Singly Linked List: Failed to create singly linked list!\n");
        return 1;
    }
    // doubly linked list 생성
    if (d_linked_list_create(&mydllist) == false) {
        printf("Doubly Linked List: Failed to create doubly linked list!\n");
        return 1;
    }

    /**** Insert first ****/
    /** Array List **/
    start = clock();    // 시간 측정 시작
    // arraylist 데이터 삽입
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (array_list_insert_first(myarrlist, e) == false) {
            printf(" Array List: Failed to insert first at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    al_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Array List의 수행시간 저장

    /** Singly Linked List **/
    start = clock();    // 시간 측정 시작
    // singly linked list 데이터 삽입
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (s_linked_list_insert_first(mysllist, e) == false) {
            printf("Singly Linked List: Failed to insert first at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    sll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Singly Linked List의 수행시간 저장

    /** Doubly Linked List **/
    start = clock();    // 시간 측정 시작
    // doubly linked list 데이터 삽입
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (d_linked_list_insert_first(mydllist, e) == false) {
            printf("Doubly Linked List: Failed to insert first at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    dll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Doubly Linked List의 수행시간 저장

    // Array List와 Linked List의 수행시간 출력
    print_performance_comparison("insert first", al_elapsed, sll_elapsed, dll_elapsed);

    /**** Delete first ****/
    /** Array List **/
    start = clock();    // 시간 측정 시작
    // arraylist 데이터 삭제
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (array_list_delete_first(myarrlist) == false) {
            printf(" Array List: Failed to delete first at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    al_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Array List의 수행시간 저장

    /** Singly Linked List **/
    start = clock();    // 시간 측정 시작
    // singly linked list 데이터 삭제
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (s_linked_list_delete_first(mysllist) == false) {
            printf("Singly Linked List: Failed to delete first at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    sll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Singly Linked List의 수행시간 저장

    /** Doubly Linked List **/
    start = clock();    // 시간 측정 시작
    // doubly linked list 데이터 삭제
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (d_linked_list_delete_first(mydllist) == false) {
            printf("Doubly Linked List: Failed to delete first at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    dll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Doubly Linked List의 수행시간 저장

    // Array List와 Linked List의 수행시간 출력
    print_performance_comparison("delete first", al_elapsed, sll_elapsed, dll_elapsed);

    /**** Insert last ****/
    /** Array List **/
    start = clock();    // 시간 측정 시작
    // arraylist 데이터 삽입
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (array_list_insert_last(myarrlist, e) == false) {
            printf(" Array List: Failed to insert last at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    al_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Array List의 수행시간 저장

    /** Singly Linked List **/
    start = clock();    // 시간 측정 시작
    // singly linked list 데이터 삽입
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (s_linked_list_insert_last(mysllist, e) == false) {
            printf("Singly Linked List: Failed to insert last at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    sll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Singly Linked List의 수행시간 저장

    /** Doubly Linked List **/
    start = clock();    // 시간 측정 시작
    // doubly linked list 데이터 삽입
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (d_linked_list_insert_last(mydllist, e) == false) {
            printf("Doubly Linked List: Failed to insert last at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    dll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Doubly Linked List의 수행시간 저장

    // Array List와 Linked List의 수행시간 출력
    print_performance_comparison("insert last", al_elapsed, sll_elapsed, dll_elapsed);

    /**** Delete last ****/
    /** Array List **/
    start = clock();    // 시간 측정 시작
    // arraylist 데이터 삭제
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (array_list_delete_last(myarrlist) == false) {
            printf(" Array List: Failed to delete last at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    al_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Array List의 수행시간 저장

    /** Singly Linked List **/
    start = clock();    // 시간 측정 시작
    // singly linked list 데이터 삭제
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (s_linked_list_delete_last(mysllist) == false) {
            printf("Singly Linked List: Failed to delete last at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    sll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Singly Linked List의 수행시간 저장

    /** Doubly Linked List **/
    start = clock();    // 시간 측정 시작
    // doubly linked list 데이터 삭제
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (d_linked_list_delete_last(mydllist) == false) {
            printf("Doubly Linked List: Failed to delete last at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    dll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Doubly Linked List의 수행시간 저장

    // Array List와 Linked List의 수행시간 출력
    print_performance_comparison("delete last", al_elapsed, sll_elapsed, dll_elapsed);

    /**** Insert index (현재 길이의 중앙 위치에) ****/
    /** Array List **/
    start = clock();    // 시간 측정 시작
    // arraylist 데이터 삽입
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (array_list_insert_index(myarrlist, e, array_list_get_size(myarrlist)/2) == false) {
            printf(" Array List: Failed to insert center at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    al_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Array List의 수행시간 저장

    /** Singly Linked List **/
    start = clock();    // 시간 측정 시작
    // singly linked list 데이터 삽입
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (s_linked_list_insert_index(mysllist, e, s_linked_list_get_size(mysllist)/2) == false) {
            printf("Singly Linked List: Failed to insert center at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    sll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Singly Linked List의 수행시간 저장

    /** Doubly Linked List **/
    start = clock();    // 시간 측정 시작
    // doubly linked list 데이터 삽입
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (d_linked_list_insert_index(mydllist, e, d_linked_list_get_size(mydllist)/2) == false) {
            printf("Doubly Linked List: Failed to insert center at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    dll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Doubly Linked List의 수행시간 저장

    // Array List와 Linked List의 수행시간 출력
    print_performance_comparison("insert center", al_elapsed, sll_elapsed, dll_elapsed);

    /**** Search by value ****/
    /** Array List **/
    start = clock();    // 시간 측정 시작
    // arraylist 데이터 검색
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (array_list_search_by_value(myarrlist, e) == -1) {
            printf(" Array List: Failed to search by value at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    al_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Array List의 수행시간 저장

    /** Singly Linked List **/
    start = clock();    // 시간 측정 시작
    // singly linked list 데이터 검색
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (s_linked_list_search_by_value(mysllist, e) == -1) {
            printf("Singly Linked List: Failed to search by value at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    sll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Singly Linked List의 수행시간 저장

    /** Doubly Linked List **/
    start = clock();    // 시간 측정 시작
    // doubly linked list 데이터 검색
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (d_linked_list_search_by_value(mydllist, e) == -1) {
            printf("Doubly Linked List: Failed to search by value at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    dll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Doubly Linked List의 수행시간 저장

    // Array List와 Linked List의 수행시간 출력
    print_performance_comparison("search value", al_elapsed, sll_elapsed, dll_elapsed);

    /**** Search by index ****/
    /** Array List **/
    start = clock();    // 시간 측정 시작
    // arraylist 데이터 검색
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (array_list_search_by_index(myarrlist, i) == NULL) {
            printf(" Array List: Failed to search by index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    al_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Array List의 수행시간 저장

    /** Singly Linked List **/
    start = clock();    // 시간 측정 시작
    // singly linked list 데이터 검색
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (s_linked_list_search_by_index(mysllist, i) == NULL) {
            printf("Singly Linked List: Failed to search by index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    sll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Singly Linked List의 수행시간 저장

    /** Doubly Linked List **/
    start = clock();    // 시간 측정 시작
    // doubly linked list 데이터 검색
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (d_linked_list_search_by_index(mydllist, i) == NULL) {
            printf("Doubly Linked List: Failed to search by index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    dll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Doubly Linked List의 수행시간 저장

    // Array List와 Linked List의 수행시간 출력
    print_performance_comparison("search index", al_elapsed, sll_elapsed, dll_elapsed);

    /**** Delete index (현재 길이의 중앙 위치에) ****/
    /** Array List **/
    start = clock();    // 시간 측정 시작
    // arraylist 데이터 삭제
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (array_list_delete_index(myarrlist, array_list_get_size(myarrlist)/2) == false) {
            printf(" Array List: Failed to delete center at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    al_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Array List의 수행시간 저장

    /** Singly Linked List **/
    start = clock();    // 시간 측정 시작
    // singly linked list 데이터 삭제
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (s_linked_list_delete_index(mysllist, s_linked_list_get_size(mysllist)/2) == false) {
            printf("Singly Linked List: Failed to delete center at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    sll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Singly Linked List의 수행시간 저장

    /** Doubly Linked List **/
    start = clock();    // 시간 측정 시작
    // doubly linked list 데이터 삭제
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (d_linked_list_delete_index(mydllist, d_linked_list_get_size(mydllist)/2) == false) {
            printf("Doubly Linked List: Failed to delete center at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    dll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Doubly Linked List의 수행시간 저장

    // Array List와 Linked List의 수행시간 출력
    print_performance_comparison("delete center", al_elapsed, sll_elapsed, dll_elapsed);

    /**** 10th index에 데이터 삽입/삭제 수행시간 측정 ****/
    /** Array List **/
    // 일단 10개 데이터 삽입
    for (int i = 0; i < 10; i++) {
        element_t e = {.value=i, .data="data"};
        if (array_list_insert_last(myarrlist, e) == false) {
            printf(" Array List: Failed to insert last at %d!\n", i);
            return 1;
        }
    }
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (array_list_insert_index(myarrlist, e, 10) == false) {
            printf(" Array List: Failed to insert index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    al_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Array List의 수행시간 저장

    /** Singly Linked List **/
    // 일단 10개 데이터 삽입
    for (int i = 0; i < 10; i++) {
        element_t e = {.value=i, .data="data"};
        if (s_linked_list_insert_first(mysllist, e) == false) {
            printf("Singly Linked List: Failed to insert first at %d!\n", i);
            return 1;
        }
    }
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (s_linked_list_insert_index(mysllist, e, 10) == false) {
            printf("Singly Linked List: Failed to insert index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    sll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Singly Linked List의 수행시간 저장

    /** Doubly Linked List **/
    // 일단 10개 데이터 삽입
    for (int i = 0; i < 10; i++) {
        element_t e = {.value=i, .data="data"};
        if (d_linked_list_insert_first(mydllist, e) == false) {
            printf("Doubly Linked List: Failed to insert first at %d!\n", i);
            return 1;
        }
    }
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (d_linked_list_insert_index(mydllist, e, 10) == false) {
            printf("Doubly Linked List: Failed to insert index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    dll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Doubly Linked List의 수행시간 저장

    // Array List와 Linked List의 수행시간 출력
    print_performance_comparison("insert f-10th", al_elapsed, sll_elapsed, dll_elapsed);

    /**** 10th index에 데이터 삭제 수행시간 측정 ****/
    /** Array List **/
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (array_list_delete_index(myarrlist, 10) == false) {
            printf(" Array List: Failed to delete index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    al_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Array List의 수행시간 저장
    // 남은 데이터 삭제
    for (int i = 0; i < 10; i++) {
        if (array_list_delete_last(myarrlist) == false) {
            printf(" Array List: Failed to delete last at %d!\n", i);
            return 1;
        }
    }

    /** Singly Linked List **/
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (s_linked_list_delete_index(mysllist, 10) == false) {
            printf("Singly Linked List: Failed to delete index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    sll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Singly Linked List의 수행시간 저장
    // 남은 데이터 삭제
    for (int i = 0; i < 10; i++) {
        if (s_linked_list_delete_first(mysllist) == false) {
            printf("Singly Linked List: Failed to delete first at %d!\n", i);
            return 1;
        }
    }

    /** Doubly Linked List **/
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (d_linked_list_delete_index(mydllist, 10) == false) {
            printf("Doubly Linked List: Failed to delete index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    dll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Doubly Linked List의 수행시간 저장
    // 남은 데이터 삭제
    for (int i = 0; i < 10; i++) {
        if (d_linked_list_delete_first(mydllist) == false) {
            printf("Doubly Linked List: Failed to delete first at %d!\n", i);
            return 1;
        }
    }

    // Array List와 Linked List의 수행시간 출력
    print_performance_comparison("delete f-10th", al_elapsed, sll_elapsed, dll_elapsed);

    /**** 끝에서 10번째 index에 데이터 삽입 수행시간 측정 ****/
    /** Array List **/
    // 일단 20개 정도 데이터 삽입
    for (int i = 0; i < 20; i++) {
        element_t e = {.value=i, .data="data"};
        if (array_list_insert_last(myarrlist, e) == false) {
            printf(" Array List: Failed to insert last at %d!\n", i);
            return 1;
        }
    }
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (array_list_insert_index(myarrlist, e, array_list_get_size(myarrlist)-10) == false) {
            printf(" Array List: Failed to insert index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    al_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Array List의 수행시간 저장

    /** Singly Linked List **/
    // 일단 20개 정도 데이터 삽입
    for (int i = 0; i < 20; i++) {
        element_t e = {.value=i, .data="data"};
        if (s_linked_list_insert_last(mysllist, e) == false) {
            printf("Singly Linked List: Failed to insert last at %d!\n", i);
            return 1;
        }
    }
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (s_linked_list_insert_index(mysllist, e, s_linked_list_get_size(mysllist)-10) == false) {
            printf("Singly Linked List: Failed to insert index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    sll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Singly Linked List의 수행시간 저장

    /** Doubly Linked List **/
    // 일단 20개 정도 데이터 삽입
    for (int i = 0; i < 20; i++) {
        element_t e = {.value=i, .data="data"};
        if (d_linked_list_insert_last(mydllist, e) == false) {
            printf("Doubly Linked List: Failed to insert last at %d!\n", i);
            return 1;
        }
    }
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (d_linked_list_insert_index(mydllist, e, d_linked_list_get_size(mydllist)-10) == false) {
            printf("Doubly Linked List: Failed to insert index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    dll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Doubly Linked List의 수행시간 저장

    // Array List와 Linked List의 수행시간 출력
    print_performance_comparison("insert l-10th", al_elapsed, sll_elapsed, dll_elapsed);

    /**** 끝에서 10번째 index 데이터 삭제 수행시간 측정 ****/
    /** Array List **/
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (array_list_delete_index(myarrlist, array_list_get_size(myarrlist)-10) == false) {
            printf(" Array List: Failed to delete index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    al_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Array List의 수행시간 저장
    // 남은 데이터 삭제
    for (int i = 0; i < 20; i++) {
        if (array_list_delete_last(myarrlist) == false) {
            printf(" Array List: Failed to delete last at %d!\n", i);
            return 1;
        }
    }

    /** Singly Linked List **/
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (s_linked_list_delete_index(mysllist, s_linked_list_get_size(mysllist)-10) == false) {
            printf("Singly Linked List: Failed to delete index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    sll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Singly Linked List의 수행시간 저장
    // 남은 데이터 삭제
    for (int i = 0; i < 20; i++) {
        if (s_linked_list_delete_last(mysllist) == false) {
            printf("Singly Linked List: Failed to delete last at %d!\n", i);
            return 1;
        }
    }

    /** Doubly Linked List **/
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (d_linked_list_delete_index(mydllist, d_linked_list_get_size(mydllist)-10) == false) {
            printf("Doubly Linked List: Failed to delete index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    dll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Doubly Linked List의 수행시간 저장
    // 남은 데이터 삭제
    for (int i = 0; i < 20; i++) {
        if (d_linked_list_delete_last(mydllist) == false) {
            printf("Doubly Linked List: Failed to delete last at %d!\n", i);
            return 1;
        }
    }

    // Array List와 Linked List의 수행시간 출력
    print_performance_comparison("delete l-10th", al_elapsed, sll_elapsed, dll_elapsed);


    /**** 메모리 해제 ****/
    // arraylist 메모리 해제
    if (array_list_destroy(&myarrlist) == false) {
        printf(" Array List: Failed to destroy array list!\n");
        return 1;
    }
    // singly linked list 메모리 해제
    if (s_linked_list_destroy(&mysllist) == false) {
        printf("Singly Linked List: Failed to destroy singly linked list!\n");
        return 1;
    }
    // doubly linked list 메모리 해제
    if (d_linked_list_destroy(&mydllist) == false) {
        printf("Doubly Linked List: Failed to destroy doubly linked list!\n");
        return 1;
    }


    return 0;
}

// 수행시간 출력을 위한 함수(자료구조 수업과는 큰 관련은 없습니다.)
void print_performance_comparison_1(char *func, double al_elapsed, double sll_elapsed, double dll_elapsed) {
    static int cnt = 0;
    if (cnt++ == 0) {
        printf("****** Performance Comparison (in second) ******\n");
        printf("                | Array List | Singly List | Doubly List |\n");
        printf("|---------------|------------|-------------|-------------|\n");
    }
    printf("| %13s |  %8lf  |  %8lf   |  %8lf   |\n", func, al_elapsed, sll_elapsed, dll_elapsed);
    printf("|---------------|------------|-------------|-------------|\n");
}
/** 더 예쁘긴 한데 실행환경의 인코딩에 따라서 잘 안보일수도... */
void print_performance_comparison_2(char *func, double al_elapsed, double sll_elapsed, double dll_elapsed) {
    static int cnt = 0;
    if (cnt++ == 0) {
        printf("****** Performance Comparison (in second) ******\n");
        printf("                ┌────────────┬─────────────┬─────────────┐\n");
        printf("                │ Array List │ Singly List │ Doubly List │\n");
        printf("┌───────────────┼────────────┼─────────────┼─────────────┤\n");
    }
    printf("│ %13s │  %8lf  │  %8lf   │  %8lf   │\n", func, al_elapsed, sll_elapsed, dll_elapsed);
    if (cnt == 12) {
        printf("└───────────────┴────────────┴─────────────┴─────────────┘\n");
    }
    else {
        printf("├───────────────┼────────────┼─────────────┼─────────────┤\n");
    }
}
void print_performance_comparison(char *func, double al_elapsed, double sll_elapsed, double dll_elapsed) {
    print_performance_comparison_1(func, al_elapsed, sll_elapsed, dll_elapsed);
    // print_performance_comparison_2(func, al_elapsed, sll_elapsed, dll_elapsed);
}