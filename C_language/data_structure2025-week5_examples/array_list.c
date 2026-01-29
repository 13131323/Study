#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "element.h"
#include "array_list.h"

#define INIT_CAPACITY 1     // 초기 용량

/**** Array List ****/
/* 함수 구현 */
bool array_list_create(array_list_t **list) {
    // arraylist 자체 메모리 할당
    *list = (array_list_t *)malloc(sizeof(array_list_t));
    if (*list == NULL) return false;

    // arraylist 초기 값 설정
    (*list)->data = NULL;
    (*list)->capacity = INIT_CAPACITY;  // 초기 용량 (구현하는 사람에 따라 다름)
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
        // 용량 2배로 증가 후 재할당
        list->capacity *= 2;
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
        // 용량 2배로 증가 후 재할당
        list->capacity *= 2;
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
        // 용량 2배로 증가 후 재할당
        list->capacity *= 2;
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

    // 데이터의 개수가 용량의 1/4 미만일 경우
    if (list->size < list->capacity / 4) {
        // 용량을 1/2로 축소 후 재할당
        list->capacity /= 2;
        list->data = (element_t *)realloc(list->data, sizeof(element_t) * list->capacity);
        if (list->data == NULL) return false; // 실패 시 false 반환
    }

    return true;
}

bool array_list_delete_last(array_list_t *list) {
    if (list == NULL) return false;       // NULL 포인터인 경우
    if (list->data == NULL) return false; // 데이터를 저장할 배열이 없는 경우
    if (list->size == 0) return false;    // 데이터의 개수가 0인 경우

    memset(list->data + list->size - 1, 0, sizeof(element_t)); // 마지막 데이터를 0으로 초기화
    list->size--;   // 데이터 개수 감소

    // 데이터의 개수가 용량의 1/4 미만일 경우
    if (list->size < list->capacity / 4) {
        // 용량을 1/2로 축소 후 재할당
        list->capacity /= 2;
        list->data = (element_t *)realloc(list->data, sizeof(element_t) * list->capacity);
        if (list->data == NULL) return false; // 실패 시 false 반환
    }

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

    // 데이터의 개수가 용량의 1/4 미만일 경우
    if (list->size < list->capacity / 4) {
        // 용량을 1/2로 축소 후 재할당
        list->capacity /= 2;
        list->data = (element_t *)realloc(list->data, sizeof(element_t) * list->capacity);
        if (list->data == NULL) return false; // 실패 시 false 반환
    }

    return true;
}

int array_list_search_by_value(array_list_t *list, element_t e) {
    if (list == NULL) return -1;         // NULL 포인터인 경우
    if (list->data == NULL) return -1;   // 데이터를 저장할 배열이 없는 경우

    for (int i = 0; i < list->size; i++) {
        if (memcmp(&(list->data[i]), &e, sizeof(element_t)) == 0) return i; // 찾은 경우 인덱스 반환
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

int array_list_get_size(array_list_t *list) {
    if (list == NULL) return -1;         // NULL 포인터인 경우
    if (list->data == NULL) return -1;   // 데이터를 저장할 배열이 없는 경우

    return list->size;  // 데이터 개수 반환
}