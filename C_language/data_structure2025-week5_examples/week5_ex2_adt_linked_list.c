/*
 * list.h 헤더파일을 기준으로 (Singly) Linked List 구현
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "week5_ex2_adt_list.h" // 헤더파일 포함

typedef struct _node_t {
    element_t element;         // 데이터
    struct _node_t *next;   // 다음 노드(아이템)의 주소
} ll_node_t;

typedef struct _linked_list_t {
    struct _node_t *head;    // 첫 번째 노드(아이템)의 주소
    int size;          // 저장하고 있는 데이터의 개수
} linked_list_t;

bool list_create(list_t *list) {     // 리스트 생성
    linked_list_t **ll_list = (linked_list_t **)(list); // linked_list_t 포인터로 형변환
    if (ll_list == NULL) return false; // NULL 포인터인 경우

    // linkedlist 자체 메모리 할당
    *ll_list = (linked_list_t *)malloc(sizeof(linked_list_t));
    if (*ll_list == NULL) return false; // 실패 시 false 반환
    
    // linkedlist 초기 값 설정
    (*ll_list)->size = 0;      // 데이터 개수 초기화
    (*ll_list)->head = NULL;   // 첫 번째 노드의 주소 초기화

    return true;
}

bool list_destroy(list_t *list) {    // 리스트 삭제
    linked_list_t **ll_list = (linked_list_t **)(list); // linked_list_t 포인터로 형변환
    if (ll_list == NULL) return false; // NULL 포인터인 경우
    if (*ll_list == NULL) return false; // 이미 해제된 메모리인 경우

    while ((*ll_list)->head != NULL) {     // 끝 노드까지 반복
        ll_node_t *p = (*ll_list)->head;        // 맨 앞 노드의 주소를 임시로 저장
        (*ll_list)->head = (*ll_list)->head->next;    // 다음 노드의 주소를 첫 번째 노드의 주소로 변경
        free(p); // 임시로 저장해둔 노드 메모리 해제
    }

    // linkedlist 메모리 해제
    free(*ll_list);
    *ll_list = NULL;   // 다시 NULL로 초기화 (잘못된 메모리에 접근하기 위함을 방지)

    return true;
}

bool list_insert(list_t list, element_t e, int index) {  // 리스트에 데이터 삽입
    linked_list_t *ll_list = (linked_list_t *)list; // linked_list_t 포인터로 형변환
    if (ll_list == NULL) return false;       // NULL 포인터인 경우
    if (index < 0 || index > ll_list->size) return false; // 범위를 벗어난 경우

    // 새로운 노드 생성
    ll_node_t *new_item = (ll_node_t *)malloc(sizeof(ll_node_t));
    if (new_item == NULL) return false;   // 실패 시 false 반환
    new_item->element = e;  // 데이터 저장
    new_item->next = NULL;  // 다음 노드의 주소 초기화

    // 노드 삽입
    if (index == 0) {   // 첫 번째 노드에 삽입하는 경우
        new_item->next = ll_list->head; // 새로운 노드의 다음 노드를 기존 첫 번째 노드로 설정
        ll_list->head = new_item;       // 새로운 노드를 첫 번째 노드로 설정
    } else {
        ll_node_t *p = ll_list->head;   // 임시로 첫 번째 노드의 주소 저장
        for (int i = 0; i < index - 1; i++) { // index - 1 번 반복 (index '전' 노드까지 이동)
            p = p->next;    // 다음 노드로 이동
        }
        new_item->next = p->next;   // 새로운 노드의 다음 노드를 이전 노드의 다음 노드로 설정
        p->next = new_item;         // 이전 노드의 다음 노드를 새로운 노드로 설정
    }
    ll_list->size++;       // 데이터 개수 증가

    return true;
}

bool list_delete(list_t list, int index) {      // 리스트에서 데이터 삭제
    linked_list_t *ll_list = (linked_list_t *)list; // linked_list_t 포인터로 형변환
    if (ll_list == NULL) return false;       // NULL 포인터인 경우
    if (ll_list->size == 0) return false;    // 데이터의 개수가 0인 경우
    if (index < 0 || index >= ll_list->size) return false; // 범위를 벗어난 경우
    
    if (index == 0) {   // 첫 번째 노드 삭제하는 경우
        ll_node_t *del_p = ll_list->head;  // 첫 번째 노드의 주소를 임시로 저장
        ll_list->head = ll_list->head->next;  // 다음 노드의 주소를 첫 번째 노드의 주소로 변경
        free(del_p);                    // 임시로 저장해둔 노드 메모리 해제
    } else {
        // 삭제할 노드 찾기
        ll_node_t *del_p = ll_list->head;   // 임시로 첫 번째 노드의 주소 저장
        for (int i = 0; i < index - 1; i++) { // index - 1 번 반복 (index '전' 노드까지 이동)
            del_p = del_p->next;    // 다음 노드로 이동
        }
        ll_node_t *del_item;
        del_item = del_p->next; // 삭제할 노드의 주소를 임시로 저장
        del_p->next = del_p->next->next; // 삭제할 노드의 '이전' 노드의 다음 노드를 삭제할 노드의 다음 노드로 변경
        free(del_item);         // 임시로 저장해둔 노드 메모리 해제
    }

    ll_list->size--;   // 데이터 개수 감소
    return true;
}

bool list_is_empty(list_t list) {                // 리스트가 비어있는지 확인
    linked_list_t *ll_list = (linked_list_t *)list; // linked_list_t 포인터로 형변환
    if (ll_list == NULL) return false;       // NULL 포인터인 경우
    return ll_list->size == 0; // 데이터의 개수가 0인 경우
}

int list_search(list_t list, element_t e) {     // 리스트에서 데이터 검색 (search by value)
    linked_list_t *ll_list = (linked_list_t *)list; // linked_list_t 포인터로 형변환
    if (ll_list == NULL) return -1;         // NULL 포인터인 경우

    ll_node_t *p = ll_list->head;   // 임시로 첫 번째 노드의 주소 저장
    for (int i = 0; i < ll_list->size; i++) {
        if (memcmp(&(p->element), &e, sizeof(element_t)) == 0) return i; // 찾은 경우 인덱스 반환
        p = p->next;    // 다음 노드로 이동
    }
    return -1;  // 찾지 못한 경우 -1 반환
}

element_t* list_get(list_t list, int index) {        // 리스트에서 데이터 가져오기 (search by index)
    linked_list_t *ll_list = (linked_list_t *)list; // linked_list_t 포인터로 형변환
    if (ll_list == NULL) return NULL;       // NULL 포인터인 경우
    if (index < 0 || index >= ll_list->size) return NULL; // 범위를 벗어난 경우

    ll_node_t *p = ll_list->head;   // 임시로 첫 번째 노드의 주소 저장
    for (int i = 0; i < index; i++) {
        p = p->next;    // 다음 노드로 이동
    }
    return &(p->element); // 데이터의 주소 반환
}

int list_get_size(list_t list) {                // 리스트의 데이터 개수 반환
    linked_list_t *ll_list = (linked_list_t *)list; // linked_list_t 포인터로 형변환
    if (ll_list == NULL) return -1;         // NULL 포인터인 경우
    return ll_list->size;  // 데이터 개수 반환
}