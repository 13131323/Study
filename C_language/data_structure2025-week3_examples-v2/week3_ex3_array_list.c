/*
 * ArrayList 구현 예제
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int element_t;      // 데이터의 타입을 재정의

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
// delete
bool array_list_delete_first (array_list_t *list);
bool array_list_delete_last  (array_list_t *list);
bool array_list_delete_index (array_list_t *list, int index);
// search
int        array_list_search_by_value (array_list_t *list, element_t e);
element_t* array_list_search_by_index (array_list_t *list, int index);
// statistics
int array_list_get_capacity (array_list_t *list);
int array_list_get_size (array_list_t *list);

/* 함수 원형은 잘 선언해두었으니까 가독성을 위해 일단 main 함수부터 */
int main(int argc, char **argv) {
    array_list_t *mylist = NULL;    // arraylist 선언

    // arraylist 생성
    if (!array_list_create(&mylist)) {
        printf("Failed to create array list!\n");
        return 1;
    }

    // arraylist에 데이터 삽입
    array_list_insert_first(mylist, 10);
    array_list_insert_last(mylist, 20);
    array_list_insert_index(mylist, 30, 1);

    // arraylist 출력
    for (int i = 0; i < array_list_get_size(mylist); i++) {
        printf("%d ", *array_list_search_by_index(mylist, i));
    }

    // arraylist 삭제
    array_list_delete_first(mylist);
    array_list_delete_last(mylist);

    // arraylist 출력
    for (int i = 0; i < array_list_get_size(mylist); i++) {
        printf("%d ", *array_list_search_by_index(mylist, i));
    }

    // arraylist 소멸 (잊지 말자 free!에 해당)
    array_list_destroy(&mylist);

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

bool array_list_delete_first(array_list_t *list) {
    if (list == NULL) return false;       // NULL 포인터인 경우
    if (list->data == NULL) return false; // 데이터를 저장할 배열이 없는 경우
    if (list->size == 0) return false;    // 데이터의 개수가 0인 경우

    // 데이터를 한 칸씩 앞으로 이동
    memmove(list->data, list->data + 1, sizeof(element_t) * (list->size - 1));
    list->size--;   // 데이터 개수 감소

    return true;
}

bool array_list_delete_last(array_list_t *list) {
    if (list == NULL) return false;       // NULL 포인터인 경우
    if (list->data == NULL) return false; // 데이터를 저장할 배열이 없는 경우
    if (list->size == 0) return false;    // 데이터의 개수가 0인 경우

    memset(list->data + list->size - 1, 0, sizeof(element_t)); // 마지막 데이터를 0으로 초기화
    list->size--;   // 데이터 개수 감소

    return true;
}

bool array_list_delete_index(array_list_t *list, int index) {
    if (list == NULL) return false;       // NULL 포인터인 경우
    if (list->data == NULL) return false; // 데이터를 저장할 배열이 없는 경우
    if (list->size == 0) return false;    // 데이터의 개수가 0인 경우
    if (index < 0 || index >= list->size) return false; // 범위를 벗어난 경우

    // index 위치부터 한 칸씩 앞으로 이동
    memmove(list->data + index, list->data + index + 1, sizeof(element_t) * (list->size - index - 1));
    list->size--;   // 데이터 개수 감소

    return true;
}

int array_list_search_by_value(array_list_t *list, element_t e) {
    if (list == NULL) return -1;         // NULL 포인터인 경우
    if (list->data == NULL) return -1;   // 데이터를 저장할 배열이 없는 경우

    for (int i = 0; i < list->size; i++) {
        if (list->data[i] == e) return i; // 찾은 경우 인덱스 반환
    }

    return -1;  // 찾지 못한 경우 -1 반환 (실제 인덱스는 0부터 시작하므로, 구현자에 따라 다르게 반환 가능)
}

element_t* array_list_search_by_index(array_list_t *list, int index) {
    if (list == NULL) return NULL;       // NULL 포인터인 경우
    if (list->data == NULL) return NULL; // 데이터를 저장할 배열이 없는 경우
    if (index < 0 || index >= list->size) return NULL; // 범위를 벗어난 경우

    return list->data + index;  // 인덱스에 해당하는 데이터의 주소 반환
    // return &list->data[index];  // 위와 동일한 표현
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