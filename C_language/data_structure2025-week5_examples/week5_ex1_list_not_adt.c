/*
 * 헤더파일을 나누지 않고 모두 한 파일에 작성한 예제
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int element_t;      // 데이터의 타입을 재정의
typedef struct _ll_node_t {
    element_t element;         // 데이터
    struct _ll_node_t *next;   // 다음 노드(아이템)의 주소
} ll_node_t;
 
typedef struct _linked_list_t {
    int size;          // 저장하고 있는 데이터의 개수
    struct _ll_node_t *head;    // 첫 번째 노드(아이템)의 주소
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
 
/* 함수 원형은 잘 선언해두었으니까 가독성을 위해 일단 main 함수부터 */
int main(int argc, char **argv) {
    linked_list_t *mylist = NULL;    // linkedlist 선언
    // linkedlist 생성
    if (!linked_list_create(&mylist)) {
        printf("Failed to create linked list!\n");
        return 1;
    }

    // linkedlist에 데이터 삽입
    linked_list_insert_first(mylist, 10);
    linked_list_insert_last(mylist, 20);
    linked_list_insert_index(mylist, 30, 1);

    // linkedlist 출력
    for (int i = 0; i < linked_list_get_size(mylist); i++) {
        printf("%d ", *linked_list_search_by_index(mylist, i));
    }
    printf("\n");

    // linkedlist 삭제
    linked_list_delete_first(mylist);
    linked_list_delete_last(mylist);

    // linkedlist 출력
    for (int i = 0; i < linked_list_get_size(mylist); i++) {
        printf("%d ", *linked_list_search_by_index(mylist, i));
    }
    printf("\n");

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

    return true;
}

bool linked_list_destroy(linked_list_t **list) {
    if (list == NULL) return false;     // NULL 포인터인 경우
    if (*list == NULL) return false;    // 이미 해제된 메모리인 경우

    while ((*list)->head != NULL) {     // 끝 노드까지 반복
        ll_node_t *p = (*list)->head;        // 맨 앞 노드의 주소를 임시로 저장
        (*list)->head = (*list)->head->next;    // 다음 노드의 주소를 첫 번째 노드의 주소로 변경
        free(p); // 임시로 저장해둔 노드 메모리 해제
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

    // 노드 삽입
    new_item->next = list->head; // 새로운 노드의 다음 노드를 기존 첫 번째 노드로 설정
    list->head = new_item;       // 새로운 노드를 첫 번째 노드로 설정

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

    // 노드 삽입
    if (list->head == NULL) {   // 첫 번째 노드가 없는 경우 (데이터의 개수가 0)
        list->head = new_item;  // 새로운 노드를 첫 번째 노드로 설정
    } else {
        ll_node_t *p = list->head;   // 임시로 첫 번째 노드의 주소 저장
        while (p->next != NULL) {    // 마지막 노드까지 반복
            p = p->next;          // 다음 노드로 이동
        }
        p->next = new_item;  // 마지막 노드의 다음 노드를 새로운 노드로 설정
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

    // 노드 삽입
    if (index == 0) {   // 첫 번째 노드에 삽입하는 경우
        new_item->next = list->head; // 새로운 노드의 다음 노드를 기존 첫 번째 노드로 설정
        list->head = new_item;       // 새로운 노드를 첫 번째 노드로 설정
    } else {
        ll_node_t *p = list->head;   // 임시로 첫 번째 노드의 주소 저장
        for (int i = 0; i < index - 1; i++) { // index - 1 번 반복 (index '전' 노드까지 이동)
            p = p->next;    // 다음 노드로 이동
        }
        new_item->next = p->next;   // 새로운 노드의 다음 노드를 이전 노드의 다음 노드로 설정
        p->next = new_item;         // 이전 노드의 다음 노드를 새로운 노드로 설정
    }
    list->size++;           // 데이터 개수 증가

    return true;
}

bool linked_list_delete_first(linked_list_t *list) {
    if (list == NULL) return false;       // NULL 포인터인 경우
    if (list->size == 0) return false;    // 데이터의 개수가 0인 경우

    // 노드 삭제
    ll_node_t *del_p = list->head;  // 첫 번째 노드의 주소를 임시로 저장
    list->head = list->head->next;  // 다음 노드의 주소를 첫 번째 노드의 주소로 변경
    free(del_p);                    // 임시로 저장해둔 노드 메모리 해제

    list->size--;   // 데이터 개수 감소

    return true;
}

bool linked_list_delete_last(linked_list_t *list) {
    if (list == NULL) return false;       // NULL 포인터인 경우
    if (list->size == 0) return false;    // 데이터의 개수가 0인 경우

    if (list->size == 1) {  // 데이터의 개수가 1인 경우 (첫 번째 노드만 존재)
        free(list->head);   // 첫 번째 노드 메모리 해제
        list->head = NULL;  // 첫 번째 노드의 주소를 NULL로 변경
        list->size--;       // 데이터 개수 감소
        return true;
    }

    // 마지막 노드 찾기
    ll_node_t *del_p = list->head;   // 임시로 첫 번째 노드의 주소 저장
    while (del_p->next->next != NULL) { // 마지막 노드의 '이전' 노드까지 반복
        del_p = del_p->next;    // 다음 노드로 이동
    }
    ll_node_t *del_item;
    del_item = del_p->next; // 마지막 노드의 주소를 임시로 저장
    del_p->next = NULL;     // 마지막 노드의 '이전' 노드의 다음 노드를 NULL로 변경
    free(del_item);         // 임시로 저장해둔 노드 메모리 해제

    list->size--;   // 데이터 개수 감소

    return true;
}

bool linked_list_delete_index(linked_list_t *list, int index) {
    if (list == NULL) return false;       // NULL 포인터인 경우
    if (list->size == 0) return false;    // 데이터의 개수가 0인 경우
    if (index < 0 || index >= list->size) return false; // 범위를 벗어난 경우

    if (index == 0) {   // 첫 번째 노드 삭제하는 경우
        return linked_list_delete_first(list);    // 첫 번째 노드 삭제
    }

    // 삭제할 노드 찾기
    ll_node_t *del_p = list->head;   // 임시로 첫 번째 노드의 주소 저장
    for (int i = 0; i < index - 1; i++) { // index - 1 번 반복 (index '전' 노드까지 이동)
        del_p = del_p->next;    // 다음 노드로 이동
    }
    ll_node_t *del_item;
    del_item = del_p->next; // 삭제할 노드의 주소를 임시로 저장
    del_p->next = del_p->next->next; // 삭제할 노드의 '이전' 노드의 다음 노드를 삭제할 노드의 다음 노드로 변경
    free(del_item);         // 임시로 저장해둔 노드 메모리 해제

    list->size--;   // 데이터 개수 감소

    return true;
}

int linked_list_search_by_value(linked_list_t *list, element_t e) {
    if (list == NULL) return -1;         // NULL 포인터인 경우

    ll_node_t *p = list->head;   // 임시로 첫 번째 노드의 주소 저장
    for (int i = 0; i < list->size; i++) {
        if (p->element == e) return i; // 찾은 경우 인덱스 반환
        p = p->next;    // 다음 노드로 이동
    }
    // size를 사용하지 않고도 구현 가능
    // while (p != NULL) {
    //     if (p->element == e) return i; // 찾은 경우 인덱스 반환
    //     p = p->next;    // 다음 노드로 이동
    // }

    return -1;  // 찾지 못한 경우 -1 반환 (실제 인덱스는 0부터 시작하므로, 구현자에 따라 다르게 반환 가능)
}

element_t* linked_list_search_by_index(linked_list_t *list, int index) {
    if (list == NULL) return NULL;       // NULL 포인터인 경우
    if (index < 0 || index >= list->size) return NULL; // 범위를 벗어난 경우

    ll_node_t *p = list->head;   // 임시로 첫 번째 노드의 주소 저장
    for (int i = 0; i < index; i++) {
        p = p->next;    // 다음 노드로 이동
    }
    return &(p->element); // 데이터의 주소 반환
}

int linked_list_get_size(linked_list_t *list) {
    if (list == NULL) return -1;         // NULL 포인터인 경우

    return list->size;  // 데이터 개수 반환

    // 만약 list 구조체에서 size 멤버를 사용하지 않는다면, 다음과 같이 구현 가능
    // ll_item_t *p = list->head;   // 임시로 첫 번째 노드의 주소 저장
    // int size = 0;
    // while (p != NULL) {
    //     size++; // 데이터 개수 증가
    //     p = p->next;    // 다음 노드로 이동
    // }
    // return size;    // 데이터 개수 반환
}