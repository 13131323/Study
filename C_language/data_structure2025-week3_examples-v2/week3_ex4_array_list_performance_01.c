/*
 * ArrayList 속도 측정 (insert)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef int element_t;      // 데이터의 타입을 재정의
#define REPEAT_CNT 100000  // 반복 횟수

typedef struct {
    element_t *data; // 데이터를 저장할 배열
    int capacity;    // 배열의 용량
    int size;        // 배열에 저장된 데이터의 개수
} array_list_t;

/* 함수 원형 */
// create / destroy
bool array_list_create  (array_list_t **list);
bool array_list_destroy (array_list_t **list);
// insert
bool array_list_insert_first (array_list_t *list, element_t e);
bool array_list_insert_last  (array_list_t *list, element_t e);
bool array_list_insert_index (array_list_t *list, element_t e, int index);
// statistics
int array_list_get_capacity (array_list_t *list);
int array_list_get_size (array_list_t *list);

/* 함수 원형은 잘 선언해두었으니까 가독성을 위해 일단 main 함수부터 */
int main(int argc, char **argv) {
    array_list_t *mylist = NULL;    // arraylist 선언
    clock_t start, end;             // 시간 측정을 위한 변수

/**** insert last 수행시간 측정 ****/
    // arraylist 생성
    if (array_list_create(&mylist) == false) {
        printf("Failed to create array list!\n");
        return 1;
    }
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (array_list_insert_last(mylist, i) == false) {
            printf("Failed to insert last at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    // 수행시간 출력
    printf("(insert last)  Elapsed time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    // arraylist 소멸 (잊지 말자 free!에 해당)
    if (array_list_destroy(&mylist) == false) {
        printf("Failed to destroy array list!\n");
        return 1;
    }
/**** insert last 수행시간 측정 끝 ****/


/**** insert first 수행시간 측정 ****/
    // arraylist 생성
    if (array_list_create(&mylist) == false) {
        printf("Failed to create array list!\n");
        return 1;
    }
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (array_list_insert_first(mylist, i) == false) {
            printf("Failed to insert first at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    // 수행시간 출력
    printf("(insert first) Elapsed time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    // arraylist 소멸 (잊지 말자 free!에 해당)
    if (array_list_destroy(&mylist) == false) {
        printf("Failed to destroy array list!\n");
        return 1;
    }
/**** insert first 수행시간 측정 끝 ****/


/**** insert index (현재 길이의 중앙 위치에) 수행시간 측정 ****/
    // arraylist 생성
    if (array_list_create(&mylist) == false) {
        printf("Failed to create array list!\n");
        return 1;
    }
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (array_list_insert_index(mylist, i, array_list_get_size(mylist)/2) == false) {
            printf("Failed to insert index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    // 수행시간 출력
    printf("(insert index) Elapsed time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    // arraylist 소멸 (잊지 말자 free!에 해당)
    if (array_list_destroy(&mylist) == false) {
        printf("Failed to destroy array list!\n");
        return 1;
    }
/**** insert index 수행시간 측정 끝 ****/

    return 0;
}


/* 함수 구현 */
bool array_list_create(array_list_t **list) {
    // arraylist 자체 메모리 할당
    *list = (array_list_t *)malloc(sizeof(array_list_t));
    if (*list == NULL) return false;

    // arraylist 초기 값 설정
    (*list)->data = NULL;
    (*list)->capacity = 1;  // 초기 용량은 1 (구현하는 사람에 따라 다름)
    (*list)->size = 0;      // 초기 데이터 개수는 0

    // arraylist 내부에 데이터를 저장할 배열 메모리 할당
    (*list)->data = (element_t *)malloc(sizeof(element_t) * (*list)->capacity);
    if ((*list)->data == NULL) {
        free(*list);    // 실패 시 arraylist 메모리도 해제해야한다.
        return false;
    }

    return true;
}

bool array_list_destroy(array_list_t **list) {
    if (list == NULL) return false;     // NULL 포인터인 경우
    if (*list == NULL) return false;    // 이미 해제된 메모리인 경우

    // arraylist 내부에 데이터를 저장할 배열 메모리 해제
    if ((*list)->data != NULL) free((*list)->data);

    // arraylist 메모리 해제
    free(*list);
    *list = NULL;   // 다시 NULL로 초기화 (잘못된 메모리에 접근하기 위함을 방지)

    return true;
}

bool array_list_insert_first(array_list_t *list, element_t e) {
    if (list == NULL) return false;     // NULL 포인터인 경우
    if (list->data == NULL) return false; // 데이터를 저장할 배열이 없는 경우

    // 배열이 꽉 찼을 경우
    if (list->size == list->capacity) {
        // 용량 증가 후 재할당
        list->capacity++;
        list->data = (element_t *)realloc(list->data, sizeof(element_t) * list->capacity);
        if (list->data == NULL) return false; // 실패 시 false 반환
    }

    // 데이터를 한 칸씩 뒤로 이동
    memmove(list->data + 1, list->data, sizeof(element_t) * list->size);

    list->data[0] = e;  // 첫 번째 위치에 데이터 저장
    list->size++;       // 데이터 개수 증가

    return true;
}

bool array_list_insert_last(array_list_t *list, element_t e) {
    if (list == NULL) return false;       // NULL 포인터인 경우
    if (list->data == NULL) return false; // 데이터를 저장할 배열이 없는 경우

    // 배열이 꽉 찼을 경우
    if (list->size == list->capacity) {
        // 용량 증가 후 재할당
        list->capacity++;
        list->data = (element_t *)realloc(list->data, sizeof(element_t) * list->capacity);
        if (list->data == NULL) return false; // 실패 시 false 반환
    }

    list->data[list->size] = e; // 마지막 위치에 데이터 저장
    list->size++;               // 데이터 개수 증가

    return true;
}

bool array_list_insert_index(array_list_t *list, element_t e, int index) {
    if (list == NULL) return false;       // NULL 포인터인 경우
    if (list->data == NULL) return false; // 데이터를 저장할 배열이 없는 경우
    if (index < 0 || index > list->size) return false; // 범위를 벗어난 경우

    // 배열이 꽉 찼을 경우
    if (list->size == list->capacity) {
        // 용량 증가 후 재할당
        list->capacity++;
        list->data = (element_t *)realloc(list->data, sizeof(element_t) * list->capacity);
        if (list->data == NULL) return false; // 실패 시 false 반환
    }

    // index 위치부터 한 칸씩 뒤로 이동
    memmove(list->data + index + 1, list->data + index, sizeof(element_t) * (list->size - index));

    list->data[index] = e;  // index 위치에 데이터 저장
    list->size++;           // 데이터 개수 증가

    return true;
}

int array_list_get_capacity(array_list_t *list) {
    if (list == NULL) return -1;         // NULL 포인터인 경우
    if (list->data == NULL) return -1;   // 데이터를 저장할 배열이 없는 경우

    return list->capacity;  // 용량 반환
}

int array_list_get_size(array_list_t *list) {
    if (list == NULL) return -1;         // NULL 포인터인 경우
    if (list->data == NULL) return -1;   // 데이터를 저장할 배열이 없는 경우

    return list->size;  // 데이터 개수 반환
}