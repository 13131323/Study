/*
 * list.h 헤더파일을 참고하여 리스트의 기능을 활용
 */

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "week5_ex2_adt_list.h" // 헤더파일 포함

#define REPEAT_CNT 10000  // 반복 횟수

int main (int argc, char **argv) {
    clock_t start, end; // 시간 측정을 위한 변수
    double elapsed; // 수행시간을 저장할 변수
    list_t mylist = NULL;    // 리스트 선언

    // 리스트 생성
    if (!list_create(&mylist)) {
        printf("Failed to create list!\n");
        return 1;
    }

    /**** insert first 수행시간 측정 ****/
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (list_insert(mylist, e, 0) == false) {
            printf("Failed to insert first at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // 수행시간 저장
    printf("Insert first: %lf seconds\n", elapsed);

    /**** delete first 수행시간 측정 ****/
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (list_delete(mylist, 0) == false) {
            printf("Failed to delete first at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // 수행시간 저장
    printf("Delete first: %lf seconds\n", elapsed);

    /**** insert last 수행시간 측정 ****/
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (list_insert(mylist, e, list_get_size(mylist)) == false) {
            printf("Failed to insert last at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // 수행시간 저장
    printf("Insert last: %lf seconds\n", elapsed);

    /**** delete last 수행시간 측정 ****/
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (list_delete(mylist, list_get_size(mylist)-1) == false) {
            printf("Failed to delete last at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // 수행시간 저장
    printf("Delete last: %lf seconds\n", elapsed);

    /***** insert index (현재 길이의 중앙 위치에) 수행시간 측정 ****/
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (list_insert(mylist, e, list_get_size(mylist)/2) == false) {
            printf("Failed to insert index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // 수행시간 저장
    printf("Insert center: %lf seconds\n", elapsed);

    /**** search by value 수행시간 측정 ****/
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (list_search(mylist, e) == -1) {
            printf("Failed to search by value at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // 수행시간 저장
    printf("Search by value: %lf seconds\n", elapsed);
    
    /**** search by index 수행시간 측정 ****/
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (list_get(mylist, i) == NULL) {
            printf("Failed to search by index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // 수행시간 저장
    printf("Search by index: %lf seconds\n", elapsed);

    /**** delete index (현재 길이의 중앙 위치에) 수행시간 측정 ****/
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (list_delete(mylist, list_get_size(mylist)/2) == false) {
            printf("Failed to delete index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // 수행시간 저장
    printf("Delete center: %lf seconds\n", elapsed);

    return 0;
}