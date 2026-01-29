/*
 * (Resizing) Array List vs (Singly) Linked List
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// element의 크기에 따라서 Array List와 Linked List의 성능차이 변화를 확인
typedef struct _element_t {
    int  value;
    char data[500];
} element_t;
#define REPEAT_CNT 10000  // 반복 횟수
#define INIT_CAPACITY 1     // 초기 용량

/**** Array List  ****/
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
int array_list_get_size (array_list_t *list);

/**** Linked List ****/
typedef struct _ll_node_t {
    element_t element;         // 데이터
    struct _ll_node_t *next;   // 다음 노드(아이템)의 주소
} ll_item_t;
 
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

// 수행시간 출력을 위한 함수(자료구조 수업과는 큰 관련은 없습니다.)
void print_performance_comparison(char *func, double al_elapsed, double ll_elapsed);

/* 함수 원형은 잘 선언해두었으니까 가독성을 위해 일단 main 함수부터 */
int main(int argc, char **argv) {
    clock_t start, end;             // 시간 측정을 위한 변수
    double al_elapsed, ll_elapsed;  // Array List와 Linked List의 수행시간을 저장할 변수

    printf("%d\n", REPEAT_CNT);

    // arraylist 생성
    array_list_t *myarrlist = NULL;    // arraylist 선언
    if (array_list_create(&myarrlist) == false) {
        printf(" Array List: Failed to create array list!\n");
        return 1;
    }
    // linkedlist 생성
    linked_list_t *myllist = NULL;  // linkedlist 선언
    if (linked_list_create(&myllist) == false) {
        printf("Linked List: Failed to create linked list!\n");
        return 1;
    }

    /**** insert first 수행시간 측정 ****/
    /** Array List **/
    start = clock();    // 시간 측정 시작
    // arraylist 데이터 삽입
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (array_list_insert_first(myarrlist, e) == false) {
            printf(" Array List: Failed to insert last at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    al_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Array List의 수행시간 저장
    /** Linked List **/
    start = clock();    // 시간 측정 시작
    // linkedlist 데이터 삽입
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (linked_list_insert_first(myllist, e) == false) {
            printf("Linked List: Failed to insert last at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    ll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Linked List의 수행시간 저장

    // Array List와 Linked List의 수행시간 출력
    print_performance_comparison("insert first", al_elapsed, ll_elapsed);

    /**** delete first 수행시간 측정 ****/
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
    /** Linked List **/
    start = clock();    // 시간 측정 시작
    // linkedlist 데이터 삭제
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (linked_list_delete_first(myllist) == false) {
            printf("Linked List: Failed to delete first at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료

    // Array List와 Linked List의 수행시간 출력
    print_performance_comparison("delete first", al_elapsed, ll_elapsed);

    /**** insert last 수행시간 측정 ****/
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
    /** Linked List **/
    start = clock();    // 시간 측정 시작
    // linkedlist 데이터 삽입
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (linked_list_insert_last(myllist, e) == false) {
            printf("Linked List: Failed to insert last at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    ll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Linked List의 수행시간 저장

    // Array List와 Linked List의 수행시간 출력
    print_performance_comparison("insert last", al_elapsed, ll_elapsed);

    /**** delete last 수행시간 측정 ****/
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
    /** Linked List **/
    start = clock();    // 시간 측정 시작
    // linkedlist 데이터 삭제
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (linked_list_delete_last(myllist) == false) {
            printf("Linked List: Failed to delete last at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    ll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Linked List의 수행시간 저장

    // Array List와 Linked List의 수행시간 출력
    print_performance_comparison("delete last", al_elapsed, ll_elapsed);

    /**** insert index (현재 길이의 중앙 위치에) 수행시간 측정 ****/
    /** Array List **/
    start = clock();    // 시간 측정 시작
    // arraylist 데이터 삽입
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (array_list_insert_index(myarrlist, e, array_list_get_size(myarrlist)/2) == false) {
            printf(" Array List: Failed to insert index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    al_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Array List의 수행시간 저장
    /** Linked List **/
    start = clock();    // 시간 측정 시작
    // linkedlist 데이터 삽입
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (linked_list_insert_index(myllist, e, linked_list_get_size(myllist)/2) == false) {
            printf("Linked List: Failed to insert index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    ll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Linked List의 수행시간 저장

    // Array List와 Linked List의 수행시간 출력
    print_performance_comparison("insert center", al_elapsed, ll_elapsed);

    /**** search by value ****/
    /** Array List **/
    start = clock();    // 시간 측정 시작
    // arraylist 데이터 검색
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (array_list_search_by_value(myarrlist, e) == -1) {
            printf(" Array List: Failed to search by value at %d!\n", i);
        }
    }
    end = clock();  // 시간 측정 종료
    al_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Array List의 수행시간 저장
    /** Linked List **/
    start = clock();    // 시간 측정 시작
    // linkedlist 데이터 검색
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (linked_list_search_by_value(myllist, e) == -1) {
            printf("Linked List: Failed to search by value at %d!\n", i);
        }
    }
    end = clock();  // 시간 측정 종료
    ll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Linked List의 수행시간 저장

    // Array List와 Linked List의 수행시간 출력
    print_performance_comparison("search value", al_elapsed, ll_elapsed);

    /**** search by index ****/
    /** Array List **/
    start = clock();    // 시간 측정 시작
    // arraylist 데이터 검색
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (array_list_search_by_index(myarrlist, i) == NULL) {
            printf(" Array List: Failed to search by index at %d!\n", i);
        }
    }
    end = clock();  // 시간 측정 종료
    al_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Array List의 수행시간 저장
    /** Linked List **/
    start = clock();    // 시간 측정 시작
    // linkedlist 데이터 검색
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (linked_list_search_by_index(myllist, i) == NULL) {
            printf("Linked List: Failed to search by index at %d!\n", i);
        }
    }
    end = clock();  // 시간 측정 종료
    ll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Linked List의 수행시간 저장

    // Array List와 Linked List의 수행시간 출력
    print_performance_comparison("search index", al_elapsed, ll_elapsed);

    /**** delete index (현재 길이의 중앙 위치에) 수행시간 측정 ****/
    /** Array List **/
    start = clock();    // 시간 측정 시작
    // arraylist 데이터 삭제
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (array_list_delete_index(myarrlist, array_list_get_size(myarrlist)/2) == false) {
            printf(" Array List: Failed to delete index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    al_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Array List의 수행시간 저장
    /** Linked List **/
    start = clock();    // 시간 측정 시작
    // linkedlist 데이터 삭제
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (linked_list_delete_index(myllist, linked_list_get_size(myllist)/2) == false) {
            printf("Linked List: Failed to delete index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    ll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Linked List의 수행시간 저장

    // Array List와 Linked List의 수행시간 출력
    print_performance_comparison("delete center", al_elapsed, ll_elapsed);

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
    /** Linked List **/
    // 일단 10개 데이터 삽입
    for (int i = 0; i < 10; i++) {
        element_t e = {.value=i, .data="data"};
        if (linked_list_insert_first(myllist, e) == false) {
            printf("Linked List: Failed to insert first at %d!\n", i);
            return 1;
        }
    }
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (linked_list_insert_index(myllist, e, 10) == false) {
            printf("Linked List: Failed to insert index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    ll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Linked List의 수행시간 저장

    // Array List와 Linked List의 수행시간 출력
    print_performance_comparison("insert f-10th", al_elapsed, ll_elapsed);


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
    /** Linked List **/
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (linked_list_delete_index(myllist, 10) == false) {
            printf("Linked List: Failed to delete index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    ll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Linked List의 수행시간 저장
    // 남은 데이터 삭제
    for (int i = 0; i < 10; i++) {
        if (linked_list_delete_first(myllist) == false) {
            printf("Linked List: Failed to delete first at %d!\n", i);
            return 1;
        }
    }

    // Array List와 Linked List의 수행시간 출력
    print_performance_comparison("delete f-10th", al_elapsed, ll_elapsed);

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
    /** Linked List **/
    // 일단 20개 정도 데이터 삽입
    for (int i = 0; i < 20; i++) {
        element_t e = {.value=i, .data="data"};
        if (linked_list_insert_first(myllist, e) == false) {
            printf("Linked List: Failed to insert first at %d!\n", i);
            return 1;
        }
    }
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        element_t e = {.value=i, .data="data"};
        if (linked_list_insert_index(myllist, e, linked_list_get_size(myllist)-10) == false) {
            printf("Linked List: Failed to insert index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    ll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Linked List의 수행시간 저장

    // Array List와 Linked List의 수행시간 출력
    print_performance_comparison("insert l-10th", al_elapsed, ll_elapsed);

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
    /** Linked List **/
    start = clock();    // 시간 측정 시작
    for (int i = 0; i < REPEAT_CNT; i++) {
        if (linked_list_delete_index(myllist, linked_list_get_size(myllist)-10) == false) {
            printf("Linked List: Failed to delete index at %d!\n", i);
            return 1;
        }
    }
    end = clock();  // 시간 측정 종료
    ll_elapsed = (double)(end - start) / CLOCKS_PER_SEC;  // Linked List의 수행시간 저장
    // 남은 데이터 삭제
    for (int i = 0; i < 20; i++) {
        if (linked_list_delete_first(myllist) == false) {
            printf("Linked List: Failed to delete first at %d!\n", i);
            return 1;
        }
    }

    // Array List와 Linked List의 수행시간 출력
    print_performance_comparison("delete l-10th", al_elapsed, ll_elapsed);

    // arraylist 소멸 (잊지 말자 free!에 해당)
    if (array_list_destroy(&myarrlist) == false) {
        printf(" Array List: Failed to destroy array list!\n");
        return 1;
    }
    // linkedlist 소멸 (잊지 말자 free!에 해당)
    if (linked_list_destroy(&myllist) == false) {
        printf("Linked List: Failed to destroy linked list!\n");
        return 1;
    }

    return 0;
}

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

/**** Linked List ****/
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
        ll_item_t *p = (*list)->head;        // 맨 앞 노드의 주소를 임시로 저장
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
    ll_item_t *new_item = (ll_item_t *)malloc(sizeof(ll_item_t));
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
    ll_item_t *new_item = (ll_item_t *)malloc(sizeof(ll_item_t));
    if (new_item == NULL) return false;   // 실패 시 false 반환
    new_item->element = e;  // 데이터 저장
    new_item->next = NULL;  // 다음 노드의 주소 초기화

    // 노드 삽입
    if (list->head == NULL) {   // 첫 번째 노드가 없는 경우 (데이터의 개수가 0)
        list->head = new_item;  // 새로운 노드를 첫 번째 노드로 설정
    } else {
        ll_item_t *p = list->head;   // 임시로 첫 번째 노드의 주소 저장
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
    ll_item_t *new_item = (ll_item_t *)malloc(sizeof(ll_item_t));
    if (new_item == NULL) return false;   // 실패 시 false 반환
    new_item->element = e;  // 데이터 저장
    new_item->next = NULL;  // 다음 노드의 주소 초기화

    // 노드 삽입
    if (index == 0) {   // 첫 번째 노드에 삽입하는 경우
        new_item->next = list->head; // 새로운 노드의 다음 노드를 기존 첫 번째 노드로 설정
        list->head = new_item;       // 새로운 노드를 첫 번째 노드로 설정
    } else {
        ll_item_t *p = list->head;   // 임시로 첫 번째 노드의 주소 저장
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
    ll_item_t *del_p = list->head;  // 첫 번째 노드의 주소를 임시로 저장
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
    ll_item_t *del_p = list->head;   // 임시로 첫 번째 노드의 주소 저장
    while (del_p->next->next != NULL) { // 마지막 노드의 '이전' 노드까지 반복
        del_p = del_p->next;    // 다음 노드로 이동
    }
    ll_item_t *del_item;
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
    ll_item_t *del_p = list->head;   // 임시로 첫 번째 노드의 주소 저장
    for (int i = 0; i < index - 1; i++) { // index - 1 번 반복 (index '전' 노드까지 이동)
        del_p = del_p->next;    // 다음 노드로 이동
    }
    ll_item_t *del_item;
    del_item = del_p->next; // 삭제할 노드의 주소를 임시로 저장
    del_p->next = del_p->next->next; // 삭제할 노드의 '이전' 노드의 다음 노드를 삭제할 노드의 다음 노드로 변경
    free(del_item);         // 임시로 저장해둔 노드 메모리 해제

    list->size--;   // 데이터 개수 감소

    return true;
}

int linked_list_search_by_value(linked_list_t *list, element_t e) {
    if (list == NULL) return -1;         // NULL 포인터인 경우

    ll_item_t *p = list->head;   // 임시로 첫 번째 노드의 주소 저장
    for (int i = 0; i < list->size; i++) {
        if (memcmp(&(p->element), &e, sizeof(element_t)) == 0) return i; // 찾은 경우 인덱스 반환
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

    ll_item_t *p = list->head;   // 임시로 첫 번째 노드의 주소 저장
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

// 수행시간 출력을 위한 함수(자료구조 수업과는 큰 관련은 없습니다.)
void print_performance_comparison_1(char *func, double al_elapsed, double ll_elapsed) {
    static int cnt = 0;
    if (cnt++ == 0) {
        printf("****** Performance Comparison (in second) ******\n");
        printf("                | Array List | Linked List |\n");
        printf("|---------------|------------|-------------|\n");
    }
    printf("| %13s |  %8lf  |  %8lf   |\n", func, al_elapsed, ll_elapsed);
    printf("|---------------|------------|-------------|\n");
}
/** 더 예쁘긴 한데 실행환경의 인코딩에 따라서 잘 안보일수도... */
void print_performance_comparison_2(char *func, double al_elapsed, double ll_elapsed) {
    static int cnt = 0;
    if (cnt++ == 0) {
        printf("****** Performance Comparison (in second) ******\n");
        printf("                ┌────────────┬─────────────┐\n");
        printf("                │ Array List │ Linked List │\n");
        printf("┌───────────────┼────────────┼─────────────┤\n");
    }
    printf("│ %13s │  %8lf  │  %8lf   │\n", func, al_elapsed, ll_elapsed);
    if (cnt == 12) {
        printf("└───────────────┴────────────┴─────────────┘\n");
    }
    else {
        printf("├───────────────┼────────────┼─────────────┤\n");
    }
}
void print_performance_comparison(char *func, double al_elapsed, double ll_elapsed) {
    print_performance_comparison_1(func, al_elapsed, ll_elapsed);
    // print_performance_comparison_2(func, al_elapsed, ll_elapsed);
}