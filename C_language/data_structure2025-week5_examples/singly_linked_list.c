#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "element.h"
#include "singly_linked_list.h"

/**** Linked List ****/
/* 함수 구현 */
bool s_linked_list_create(s_linked_list_t **list) {
    if (list == NULL) return false;  // NULL 포인터인 경우

    // linkedlist 자체 메모리 할당
    *list = (s_linked_list_t *)malloc(sizeof(s_linked_list_t));
    if (*list == NULL) return false;

    // linkedlist 초기 값 설정
    (*list)->size = 0;      // 데이터 개수 초기화
    (*list)->head = NULL;   // 첫 번째 노드의 주소 초기화

    return true;
}

bool s_linked_list_destroy(s_linked_list_t **list) {
    if (list == NULL) return false;     // NULL 포인터인 경우
    if (*list == NULL) return false;    // 이미 해제된 메모리인 경우

    while ((*list)->head != NULL) {     // 끝 노드까지 반복
        s_ll_node_t *p = (*list)->head;        // 맨 앞 노드의 주소를 임시로 저장
        (*list)->head = (*list)->head->next;    // 다음 노드의 주소를 첫 번째 노드의 주소로 변경
        free(p); // 임시로 저장해둔 노드 메모리 해제
    }

    // linkedlist 메모리 해제
    free(*list);
    *list = NULL;   // 다시 NULL로 초기화 (잘못된 메모리에 접근하기 위함을 방지)

    return true;
}

bool s_linked_list_insert_first(s_linked_list_t *list, element_t e) {
    if (list == NULL) return false;     // NULL 포인터인 경우
    
    // 새로운 노드 생성
    s_ll_node_t *new_item = (s_ll_node_t *)malloc(sizeof(s_ll_node_t));
    if (new_item == NULL) return false; // 실패 시 false 반환
    new_item->element = e;  // 데이터 저장
    new_item->next = NULL;  // 다음 노드의 주소 초기화

    // 노드 삽입
    new_item->next = list->head; // 새로운 노드의 다음 노드를 기존 첫 번째 노드로 설정
    list->head = new_item;       // 새로운 노드를 첫 번째 노드로 설정

    list->size++;       // 데이터 개수 증가

    return true;
}

bool s_linked_list_insert_last(s_linked_list_t *list, element_t e) {
    if (list == NULL) return false;       // NULL 포인터인 경우

    // 새로운 노드 생성
    s_ll_node_t *new_item = (s_ll_node_t *)malloc(sizeof(s_ll_node_t));
    if (new_item == NULL) return false;   // 실패 시 false 반환
    new_item->element = e;  // 데이터 저장
    new_item->next = NULL;  // 다음 노드의 주소 초기화

    // 노드 삽입
    if (list->head == NULL) {   // 첫 번째 노드가 없는 경우 (데이터의 개수가 0)
        list->head = new_item;  // 새로운 노드를 첫 번째 노드로 설정
    } else {
        s_ll_node_t *p = list->head;   // 임시로 첫 번째 노드의 주소 저장
        while (p->next != NULL) {    // 마지막 노드까지 반복
            p = p->next;          // 다음 노드로 이동
        }
        p->next = new_item;  // 마지막 노드의 다음 노드를 새로운 노드로 설정
    }

    list->size++;               // 데이터 개수 증가

    return true;
}

bool s_linked_list_insert_index(s_linked_list_t *list, element_t e, int index) {
    if (list == NULL) return false;       // NULL 포인터인 경우
    if (index < 0 || index > list->size) return false; // 범위를 벗어난 경우

    // 새로운 노드 생성
    s_ll_node_t *new_item = (s_ll_node_t *)malloc(sizeof(s_ll_node_t));
    if (new_item == NULL) return false;   // 실패 시 false 반환
    new_item->element = e;  // 데이터 저장
    new_item->next = NULL;  // 다음 노드의 주소 초기화

    // 노드 삽입
    if (index == 0)   // 첫 번째 노드에 삽입하는 경우
        return s_linked_list_insert_first(list, e);    // 첫 번째 노드 삽입 else {
        
    s_ll_node_t *p = list->head;   // 임시로 첫 번째 노드의 주소 저장
    for (int i = 0; i < index - 1; i++) { // index - 1 번 반복 (index '전' 노드까지 이동)
        p = p->next;    // 다음 노드로 이동
    }
    new_item->next = p->next;   // 새로운 노드의 다음 노드를 이전 노드의 다음 노드로 설정
    p->next = new_item;         // 이전 노드의 다음 노드를 새로운 노드로 설정
    list->size++;           // 데이터 개수 증가

    return true;
}

bool s_linked_list_delete_first(s_linked_list_t *list) {
    if (list == NULL) return false;       // NULL 포인터인 경우
    if (list->size == 0) return false;    // 데이터의 개수가 0인 경우

    // 노드 삭제
    s_ll_node_t *del_p = list->head;  // 첫 번째 노드의 주소를 임시로 저장
    list->head = list->head->next;  // 다음 노드의 주소를 첫 번째 노드의 주소로 변경
    free(del_p);                    // 임시로 저장해둔 노드 메모리 해제

    list->size--;   // 데이터 개수 감소

    return true;
}

bool s_linked_list_delete_last(s_linked_list_t *list) {
    if (list == NULL) return false;       // NULL 포인터인 경우
    if (list->size == 0) return false;    // 데이터의 개수가 0인 경우

    if (list->size == 1) {  // 데이터의 개수가 1인 경우 (첫 번째 노드만 존재)
        free(list->head);   // 첫 번째 노드 메모리 해제
        list->head = NULL;  // 첫 번째 노드의 주소를 NULL로 변경
        list->size--;       // 데이터 개수 감소
        return true;
    }

    // 마지막 노드 찾기
    s_ll_node_t *del_p = list->head;   // 임시로 첫 번째 노드의 주소 저장
    while (del_p->next->next != NULL) { // 마지막 노드의 '이전' 노드까지 반복
        del_p = del_p->next;    // 다음 노드로 이동
    }
    s_ll_node_t *del_item;
    del_item = del_p->next; // 마지막 노드의 주소를 임시로 저장
    del_p->next = NULL;     // 마지막 노드의 '이전' 노드의 다음 노드를 NULL로 변경
    free(del_item);         // 임시로 저장해둔 노드 메모리 해제

    list->size--;   // 데이터 개수 감소

    return true;
}

bool s_linked_list_delete_index(s_linked_list_t *list, int index) {
    if (list == NULL) return false;       // NULL 포인터인 경우
    if (list->size == 0) return false;    // 데이터의 개수가 0인 경우
    if (index < 0 || index >= list->size) return false; // 범위를 벗어난 경우

    if (index == 0) {   // 첫 번째 노드 삭제하는 경우
        return s_linked_list_delete_first(list);    // 첫 번째 노드 삭제
    }

    // 삭제할 노드 찾기
    s_ll_node_t *del_p = list->head;   // 임시로 첫 번째 노드의 주소 저장
    for (int i = 0; i < index - 1; i++) { // index - 1 번 반복 (index '전' 노드까지 이동)
        del_p = del_p->next;    // 다음 노드로 이동
    }
    s_ll_node_t *del_item;
    del_item = del_p->next; // 삭제할 노드의 주소를 임시로 저장
    del_p->next = del_p->next->next; // 삭제할 노드의 '이전' 노드의 다음 노드를 삭제할 노드의 다음 노드로 변경
    free(del_item);         // 임시로 저장해둔 노드 메모리 해제

    list->size--;   // 데이터 개수 감소

    return true;
}

int s_linked_list_search_by_value(s_linked_list_t *list, element_t e) {
    if (list == NULL) return -1;         // NULL 포인터인 경우

    s_ll_node_t *p = list->head;   // 임시로 첫 번째 노드의 주소 저장
    for (int i = 0; i < list->size; i++) {
        if (memcmp(&(p->element), &e, sizeof(element_t)) == 0) return i; // 찾은 경우 인덱스 반환
        p = p->next;    // 다음 노드로 이동
    }

    return -1;  // 찾지 못한 경우 -1 반환 (실제 인덱스는 0부터 시작하므로, 구현자에 따라 다르게 반환 가능)
}

element_t* s_linked_list_search_by_index(s_linked_list_t *list, int index) {
    if (list == NULL) return NULL;       // NULL 포인터인 경우
    if (index < 0 || index >= list->size) return NULL; // 범위를 벗어난 경우

    s_ll_node_t *p = list->head;   // 임시로 첫 번째 노드의 주소 저장
    for (int i = 0; i < index; i++) {
        p = p->next;    // 다음 노드로 이동
    }
    return &(p->element); // 데이터의 주소 반환
}

int s_linked_list_get_size(s_linked_list_t *list) {
    if (list == NULL) return -1;         // NULL 포인터인 경우

    return list->size;  // 데이터 개수 반환
}