/*
 * list.h 헤더파일을 기준으로 ArrayList 구현
 */

#include <stdbool.h>
#include <stdlib.h>    
#include <string.h>
#include "week5_ex2_adt_list.h" // 헤더파일 포함

#define INIT_CAPACITY 1     // 초기 용량

typedef struct _array_list_t {
    element_t *data; // 데이터를 저장할 배열
    int capacity;    // 배열의 용량
    int size;        // 배열에 저장된 데이터의 개수
} array_list_t;

bool list_create(list_t *list) {     // 리스트 생성
    array_list_t **arr_list = (array_list_t **)(list);
    if (arr_list == NULL) return false; // NULL 포인터인 경우

    // arraylist 자체 메모리 할당
    *arr_list = (array_list_t *)malloc(sizeof(array_list_t));
    if (*arr_list == NULL) return false; // 실패 시 false 반환

    (*arr_list)->capacity = INIT_CAPACITY;  // 초기 용량
    (*arr_list)->size = 0;      // 초기 데이터 개수는 0
    (*arr_list)->data = (element_t *)malloc(sizeof(element_t) * (*arr_list)->capacity); // 배열 메모리 할당

    return (*arr_list)->data != NULL; // 배열 메모리 할당 성공 여부 반환
}

bool list_destroy(list_t *list) {    // 리스트 삭제
    array_list_t **arr_list = (array_list_t **)(list); // array_list_t 포인터로 형변환

    if (arr_list == NULL) return false; // NULL 포인터인 경우
    if (*arr_list == NULL) return false; // 이미 해제된 메모리인 경우

    free((*arr_list)->data); // 배열 메모리 해제
    free(*arr_list);         // arraylist 메모리 해제
    *arr_list = NULL;   // 다시 NULL로 초기화 (잘못된 메모리에 접근하기 위함을 방지)

    return true;        // 성공 시 true 반환
}

bool list_insert(list_t list, element_t e, int index) {  // 리스트에 데이터 삽입
    array_list_t *arr_list = (array_list_t *)list; // array_list_t 포인터로 형변환

    if (arr_list == NULL) return false;       // NULL 포인터인 경우
    if (index < 0 || index > arr_list->size) return false; // 범위를 벗어난 경우

    // 배열이 꽉 찼을 경우
    if (arr_list->size == arr_list->capacity) {
        // 용량 2배로 증가 후 재할당
        arr_list->capacity *= 2;
        arr_list->data = (element_t *)realloc(arr_list->data, sizeof(element_t) * arr_list->capacity);
        if (arr_list->data == NULL) return false; // 실패 시 false 반환
    }

    // insert last가 아닌 경우 원소를 이동
    if (index < arr_list->size) // insert first or insert index
        memmove(arr_list->data + index + 1, arr_list->data + index, sizeof(element_t) * (arr_list->size - index));

    arr_list->data[index] = e;  // index 위치에 데이터 저장
    arr_list->size++;           // 데이터 개수 증가

    return true;
}

bool list_delete(list_t list, int index) {      // 리스트에서 데이터 삭제
    array_list_t *arr_list = (array_list_t *)list; // array_list_t 포인터로 형변환

    if (arr_list == NULL) return false;       // NULL 포인터인 경우
    if (arr_list->size == 0) return false;    // 데이터의 개수가 0인 경우
    if (arr_list->data == NULL) return false; // 데이터를 저장할 배열이 없는 경우
    if (index < 0 || index >= arr_list->size) return false; // 범위를 벗어난 경우

    // insert last가 아닌 경우 원소를 이동
    if (index < arr_list->size - 1) { // insert first or insert index
        memmove(arr_list->data + index, arr_list->data + index + 1, sizeof(element_t) * (arr_list->size - index - 1));
    }
    arr_list->size--;   // 데이터 개수 감소

    if (arr_list->size < arr_list->capacity / 4) { // 데이터의 개수가 용량의 1/4 미만일 경우
        // 용량을 1/2로 축소 후 재할당
        arr_list->capacity /= 2;
        arr_list->data = (element_t *)realloc(arr_list->data, sizeof(element_t) * arr_list->capacity);
        if (arr_list->data == NULL) return false; // 실패 시 false 반환
    }

    return true; // 성공 시 true 반환
}

bool list_is_empty(list_t list) {                // 리스트가 비어있는지 확인
    array_list_t *arr_list = (array_list_t *)list; // array_list_t 포인터로 형변환

    if (arr_list == NULL) return false;       // NULL 포인터인 경우
    if (arr_list->data == NULL) return false; // 데이터를 저장할 배열이 없는 경우
    return arr_list->size == 0;               // 데이터 개수가 0이면 true 반환
}

int  list_search(list_t list, element_t e) {     // 리스트에서 데이터 검색 (search by value)
    array_list_t *arr_list = (array_list_t *)list; // array_list_t 포인터로 형변환

    if (arr_list == NULL) return -1;         // NULL 포인터인 경우
    if (arr_list->data == NULL) return -1;   // 데이터를 저장할 배열이 없는 경우
    
    for (int i = 0; i < arr_list->size; i++) {
        if (memcmp(&(arr_list->data[i]), &e, sizeof(element_t)) == 0) return i; // 찾은 경우 인덱스 반환
    }
    return -1; // 찾지 못한 경우 -1 반환
}

element_t* list_get(list_t list, int index) {        // 리스트에서 데이터 가져오기 (search by index)
    array_list_t *arr_list = (array_list_t *)list; // array_list_t 포인터로 형변환

    if (arr_list == NULL) return NULL;       // NULL 포인터인 경우
    if (arr_list->data == NULL) return NULL; // 데이터를 저장할 배열이 없는 경우
    if (index < 0 || index >= arr_list->size) return NULL; // 범위를 벗어난 경우
    if (arr_list->size == 0) return NULL; // 데이터의 개수가 0인 경우

    return arr_list->data + index;  // 인덱스에 해당하는 데이터의 주소 반환
}

int  list_get_size(list_t list) {                // 리스트의 데이터 개수 반환
    array_list_t *arr_list = (array_list_t *)list; // array_list_t 포인터로 형변환

    if (arr_list == NULL) return -1;         // NULL 포인터인 경우
    if (arr_list->data == NULL) return -1;   // 데이터를 저장할 배열이 없는 경우
    return arr_list->size;                   // 데이터 개수 반환
}