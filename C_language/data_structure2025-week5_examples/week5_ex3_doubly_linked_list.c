/*
 * Doubly Linked List
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int element_t;      // 데이터의 타입을 재정의
typedef struct _ll_node_t {
    element_t element;         // 데이터
    struct _ll_node_t *next;   // 다음 노드(아이템)의 주소
    struct _ll_node_t *prev;   // 이전 노드(아이템)의 주소
} ll_node_t;
 
typedef struct _linked_list_t {
    int size;          // 저장하고 있는 데이터의 개수
    struct _ll_node_t *head;    // 첫 번째 노드(아이템)의 주소
    struct _ll_node_t *tail;    // 마지막 노드(아이템)의 주소
} linked_list_t;
 
/* 함수 원형 */
// create / destroy
bool linked_list_create  (linked_list_t **list);
bool linked_list_destroy (linked_list_t **list);
// insert
bool linked_list_insert_first (linked_list_t *list, element_t e);
bool linked_list_insert_last  (linked_list_t *list, element_t e);
bool linked_list_insert_index (linked_list_t *list, element_t e, int index);
// delete
bool linked_list_delete_first (linked_list_t *list);
bool linked_list_delete_last  (linked_list_t *list);
bool linked_list_delete_index (linked_list_t *list, int index);
// search
int linked_list_search_by_value (linked_list_t *list, element_t e);
element_t* linked_list_search_by_index (linked_list_t *list, int index);
// statistics
int linked_list_get_size (linked_list_t *list);
void linked_list_print (linked_list_t *list);
 
/* 함수 원형은 잘 선언해두었으니까 가독성을 위해 일단 main 함수부터 */
int main(int argc, char **argv) {
    linked_list_t *mylist = NULL;    // linkedlist 선언
    // linkedlist 생성
    if (!linked_list_create(&mylist)) {
        printf("Failed to create linked list!\n");
        return 1;
    }

    // linkedlist에 데이터 삽입
    printf("insert first 10\n");
    linked_list_insert_first(mylist, 10);
    linked_list_print(mylist);

    printf("insert last 20\n");
    linked_list_insert_last(mylist, 20);
    linked_list_print(mylist);

    printf("insert last 30\n");
    linked_list_insert_last(mylist, 30);
    linked_list_print(mylist);

    printf("insert last 40\n");
    linked_list_insert_last(mylist, 40);
    linked_list_print(mylist);

    printf("insert first 50\n");
    linked_list_insert_first(mylist, 50);
    linked_list_print(mylist);

    printf("insert first 60\n");
    linked_list_insert_first(mylist, 60);
    linked_list_print(mylist);

    // linkedlist 끝쪽에 데이터 삽입
    printf("insert index 70 at 4\n");
    linked_list_insert_index(mylist, 70, 4);
    linked_list_print(mylist);

    // linkedlist 앞쪽에 데이터 삽입
    printf("insert index 80 at 2\n");
    linked_list_insert_index(mylist, 80, 2);
    linked_list_print(mylist);

    // 끝쪽 데이터 삭제
    printf("delete index 5\n");
    linked_list_delete_index(mylist, 5);
    linked_list_print(mylist);

    // 앞쪽 데이터 삭제
    printf("delete index 1\n");
    linked_list_delete_index(mylist, 1);
    linked_list_print(mylist);

    // 첫 데이터 삭제
    printf("delete first\n");
    linked_list_delete_first(mylist);
    linked_list_print(mylist);

    // 마지막 데이터 삭제
    printf("delete last\n");
    linked_list_delete_last(mylist);
    linked_list_print(mylist);

    // linkedlist 소멸 (잊지 말자 free!에 해당)
    linked_list_destroy(&mylist);

    return 0;
}

/* 함수 구현 */
bool linked_list_create(linked_list_t **list) {
    if (list == NULL) return false;  // NULL 포인터인 경우

    // linkedlist 자체 메모리 할당
    *list = (linked_list_t *)malloc(sizeof(linked_list_t));
    if (*list == NULL) return false;

    // linkedlist 초기 값 설정
    (*list)->size = 0;      // 데이터 개수 초기화
    (*list)->head = NULL;   // 첫 번째 노드의 주소 초기화
    (*list)->tail = NULL;   // 마지막 노드의 주소 초기화

    return true;
}

bool linked_list_destroy(linked_list_t **list) {
    if (list == NULL) return false;     // NULL 포인터인 경우
    if (*list == NULL) return false;    // 이미 해제된 메모리인 경우

    ll_node_t *current = (*list)->head; // 현재 노드의 주소를 저장
    while (current != NULL) {     // 끝 노드까지 반복
        ll_node_t *del_p = current; // 현재 노드의 주소를 임시로 저장
        current = current->next;    // 다음 노드로 이동
        free(del_p);               // 임시로 저장해둔 노드 메모리 해제
    }

    // linkedlist 메모리 해제
    free(*list);
    *list = NULL;   // 다시 NULL로 초기화 (잘못된 메모리에 접근하기 위함을 방지)

    return true;
}

bool linked_list_insert_first(linked_list_t *list, element_t e) {
    if (list == NULL) return false;     // NULL 포인터인 경우
    
    // 새로운 노드 생성
    ll_node_t *new_item = (ll_node_t *)malloc(sizeof(ll_node_t));
    if (new_item == NULL) return false; // 실패 시 false 반환
    new_item->element = e;  // 데이터 저장
    new_item->next = NULL;  // 다음 노드의 주소 초기화
    new_item->prev = NULL;  // 이전 노드의 주소 초기화

    // 노드 삽입
    if (list->head == NULL) {   // 리스트가 비어있는 경우
        list->head = new_item;  // 새로운 노드를 첫 번째 노드로 설정
        list->tail = new_item;  // 새로운 노드를 마지막 노드로 설정
    } else {
        new_item->next = list->head; // 새로운 노드의 다음 노드를 기존 첫 번째 노드로 설정
        list->head->prev = new_item; // 기존 첫 번째 노드의 이전 노드를 새로운 노드로 설정
        list->head = new_item;       // 새로운 노드를 첫 번째 노드로 설정
    }

    list->size++;       // 데이터 개수 증가

    return true;
}

bool linked_list_insert_last(linked_list_t *list, element_t e) {
    if (list == NULL) return false;       // NULL 포인터인 경우

    // 새로운 노드 생성
    ll_node_t *new_item = (ll_node_t *)malloc(sizeof(ll_node_t));
    if (new_item == NULL) return false;   // 실패 시 false 반환
    new_item->element = e;  // 데이터 저장
    new_item->next = NULL;  // 다음 노드의 주소 초기화
    new_item->prev = NULL;  // 이전 노드의 주소 초기화

    // 노드 삽입
    if (list->head == NULL) {   // 리스트가 비어있는 경우
        list->head = new_item;  // 새로운 노드를 첫 번째 노드로 설정
        list->tail = new_item;  // 새로운 노드를 마지막 노드로 설정
    } else {
        list->tail->next = new_item;   // 마지막 노드의 다음 노드를 새로운 노드로 설정
        new_item->prev = list->tail;   // 새로운 노드의 이전 노드를 마지막 노드로 설정
        list->tail = new_item;         // 새로운 노드를 마지막 노드로 설정
    }

    list->size++;               // 데이터 개수 증가

    return true;
}

bool linked_list_insert_index(linked_list_t *list, element_t e, int index) {
    if (list == NULL) return false;       // NULL 포인터인 경우
    if (index < 0 || index > list->size) return false; // 범위를 벗어난 경우

    // 새로운 노드 생성
    ll_node_t *new_item = (ll_node_t *)malloc(sizeof(ll_node_t));
    if (new_item == NULL) return false;   // 실패 시 false 반환
    new_item->element = e;  // 데이터 저장
    new_item->next = NULL;  // 다음 노드의 주소 초기화
    new_item->prev = NULL;  // 이전 노드의 주소 초기화

    // 노드 삽입
    if (list->head == NULL)         // 리스트가 비어있는 경우
        return linked_list_insert_first(list, e);
    else if (index == 0)            // 첫 번째 노드에 삽입하는 경우
        return linked_list_insert_first(list, e);
    else if (index == list->size)   // 마지막 노드에 삽입하는 경우
        return linked_list_insert_last(list, e);

    ll_node_t *p = NULL;
    // 그 외의 경우 (중간에 삽입하는 경우)
    if (index > list->size / 2) { // index가 중간보다 큰 경우
        p = list->tail;   // 임시로 마지막 노드의 주소 저장
        for (int i = list->size - 1; i >= index; i--)
            p = p->prev;    // 이전 노드로 이동
    }
    else { // index가 중간보다 작은 경우
        p = list->head;   // 임시로 첫 번째 노드의 주소 저장
        for (int i = 0; i < index - 1; i++)
            p = p->next;    // 다음 노드로 이동
    }
    new_item->next = p->next; // 새로운 노드의 다음 노드를 현재 노드의 다음 노드로 설정
    new_item->prev = p;       // 새로운 노드의 이전 노드를 현재 노드로 설정
    p->next->prev = new_item; // 다음 노드의 이전 노드를 새로운 노드로 설정
    p->next = new_item;       // 현재 노드의 다음 노드를 새로운 노드로 설정
    list->size++;           // 데이터 개수 증가

    return true;
}

bool linked_list_delete_first(linked_list_t *list) {
    if (list == NULL) return false;       // NULL 포인터인 경우
    if (list->size == 0) return false;    // 데이터의 개수가 0인 경우

    ll_node_t *del_p = list->head;  // 첫 번째 노드의 주소를 임시로 저장
    if (list->size == 1) {  // 데이터의 개수가 1인 경우 (첫 번째 노드만 존재)
        list->head = NULL;  // 첫 번째 노드의 주소를 NULL로 변경
        list->tail = NULL;  // 마지막 노드의 주소를 NULL로 변경
    }
    else {  // 데이터의 개수가 2 이상인 경우
        list->head = list->head->next;  // 다음 노드의 주소를 첫 번째 노드의 주소로 변경
        list->head->prev = NULL;        // 첫 번째 노드의 이전 노드를 NULL로 변경
    }

    // 노드 삭제
    free(del_p); // 임시로 저장해둔 노드 메모리 해제

    list->size--;   // 데이터 개수 감소

    return true;
}

bool linked_list_delete_last(linked_list_t *list) {
    if (list == NULL) return false;       // NULL 포인터인 경우
    if (list->size == 0) return false;    // 데이터의 개수가 0인 경우

    ll_node_t *del_p = list->tail;  // 마지막 노드의 주소를 임시로 저장
    if (list->size == 1) {  // 데이터의 개수가 1인 경우 (첫 번째 노드만 존재)
        list->head = NULL;  // 첫 번째 노드의 주소를 NULL로 변경
        list->tail = NULL;  // 마지막 노드의 주소를 NULL로 변경
    }
    else {
        list->tail = list->tail->prev;  // 이전 노드의 주소를 마지막 노드의 주소로 변경
        list->tail->next = NULL;        // 마지막 노드의 다음 노드를 NULL로 변경
    }

    // 노드 삭제
    free(del_p); // 임시로 저장해둔 노드 메모리 해제

    list->size--;   // 데이터 개수 감소

    return true;
}

bool linked_list_delete_index(linked_list_t *list, int index) {
    if (list == NULL) return false;       // NULL 포인터인 경우
    if (list->size == 0) return false;    // 데이터의 개수가 0인 경우
    if (index < 0 || index >= list->size) return false; // 범위를 벗어난 경우

    if (index == 0) // 첫 번째 노드를 삭제하는 경우
        return linked_list_delete_first(list);
    if (index == list->size - 1) // 마지막 노드를 삭제하는 경우
        return linked_list_delete_last(list);

    // 삭제할 노드 찾기
    ll_node_t *del_p = NULL, *p = NULL;
    // 그 외의 경우 (중간에 삽입하는 경우)
    if (index > list->size / 2) { // index가 중간보다 큰 경우
        p = list->tail;   // 임시로 마지막 노드의 주소 저장
        for (int i = list->size - 1; i > index; i--)
            p = p->prev;    // 이전 노드로 이동
    }
    else { // index가 중간보다 작은 경우
        p = list->head;   // 임시로 첫 번째 노드의 주소 저장
        for (int i = 0; i < index; i++)
            p = p->next;    // 다음 노드로 이동
    }
    del_p = p; // 삭제할 노드의 주소를 임시로 저장
    p->prev->next = p->next; // 삭제할 노드의 '이전' 노드의 다음 노드를 삭제할 노드의 다음 노드로 변경
    p->next->prev = p->prev; // 삭제할 노드의 '다음' 노드의 이전 노드를 삭제할 노드의 이전 노드로 변경
    free(del_p); // 임시로 저장해둔 노드 메모리 해제

    list->size--;   // 데이터 개수 감소

    return true;
}

int linked_list_search_by_value(linked_list_t *list, element_t e) {
    if (list == NULL) return -1;         // NULL 포인터인 경우

    ll_node_t *p = list->head;   // 임시로 첫 번째 노드의 주소 저장
    for (int i = 0; i < list->size; i++) {
        if (memcmp(&(p->element), &e, sizeof(element_t)) == 0) return i; // 찾은 경우 인덱스 반환
        p = p->next;    // 다음 노드로 이동
    }

    return -1;  // 찾지 못한 경우 -1 반환 (실제 인덱스는 0부터 시작하므로, 구현자에 따라 다르게 반환 가능)
}

element_t* linked_list_search_by_index(linked_list_t *list, int index) {
    if (list == NULL) return NULL;       // NULL 포인터인 경우
    if (index < 0 || index >= list->size) return NULL; // 범위를 벗어난 경우

    ll_node_t *p = NULL;
    if (index > list->size / 2) { // index가 중간보다 큰 경우
        p = list->tail;   // 마지막노드 부터
        for (int i = list->size - 1; i > index; i--)
            p = p->prev;    // 이전 노드로 이동
    }
    else { // index가 중간보다 작은 경우
        p = list->head;   // 첫 번째 노드 부터
        for (int i = 0; i < index; i++)
            p = p->next;    // 다음 노드로 이동
    }

    return &(p->element); // 데이터의 주소 반환
}

int linked_list_get_size(linked_list_t *list) {
    if (list == NULL) return -1;         // NULL 포인터인 경우
    return list->size;  // 데이터 개수 반환
}

void linked_list_print (linked_list_t *list) {
    if (list == NULL) return;     // NULL 포인터인 경우
    if (list->size == 0) return;  // 데이터의 개수가 0인 경우

    ll_node_t *p = list->head;   // 임시로 첫 번째 노드의 주소 저장
    for (int i = 0; i < list->size; i++) {
        printf("%d ", p->element); // 데이터 출력
        p = p->next;    // 다음 노드로 이동
    }
    printf("\n");
}