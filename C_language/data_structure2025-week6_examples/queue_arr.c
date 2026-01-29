#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "element.h"
#include "queue_arr.h"

bool arr_queue_resize(arr_queue_t **queue, int new_capacity) {
    if (queue == NULL) return false;  // NULL 포인터인 경우
    if (*queue == NULL) return false; // queue가 NULL인 경우
    if ((*queue)->data == NULL) return false; // 데이터 배열이 NULL인 경우

    /** 임시 queue 생성 **/
    arr_queue_t *tmp_queue = (arr_queue_t *)malloc(sizeof(arr_queue_t)); // 새로운 큐 구조체 메모리 할당
    if (tmp_queue == NULL) return false; // 메모리 할당 실패
    tmp_queue->size = 0; // 큐의 크기 초기화
    tmp_queue->front = 0; // 큐의 맨 앞 인덱스 초기화
    tmp_queue->rear  = 0; // 큐의 맨 뒤 인덱스 초기화
    tmp_queue->capacity = (*queue)->capacity; // 큐의 최대 크기 설정
    tmp_queue->data     = (element_t *)malloc(sizeof(element_t) * tmp_queue->capacity); // 데이터 배열 메모리 할당
    if (tmp_queue->data == NULL) { // 메모리 할당 실패
        free(tmp_queue); // 큐 구조체 메모리 해제
        return false;
    }

    // 이동
    while (arr_queue_is_empty(*queue) != true) { // 기존 큐가 빌 때까지 반복
        element_t e;
        arr_queue_dequeue(*queue, &e); // 큐에서 데이터 삭제
        arr_queue_enqueue(tmp_queue, e); // 새로운 큐에 데이터 삽입
    }

    (*queue)->capacity = new_capacity; // 기존 큐의 용량 재설정
    (*queue)->data = (element_t *)realloc((*queue)->data, sizeof(element_t) * new_capacity); // 메모리 재할당
    if ((*queue)->data == NULL) { // 메모리 재할당 실패
        free(tmp_queue->data); // 새로운 큐의 데이터 배열 메모리 해제
        free(tmp_queue); // 새로운 큐 구조체 메모리 해제
        return false;
    }
    // 기존 큐 초기화
    (*queue)->size  = 0;    (*queue)->front = 0;    (*queue)->rear  = 0;
    memset((*queue)->data, 0, sizeof(element_t) * new_capacity); // 데이터 배열 초기화

    // 다시 복사
    while (arr_queue_is_empty(tmp_queue) != true) { // 새로운 큐가 빌 때까지 반복
        element_t e;
        arr_queue_dequeue(tmp_queue, &e); // 임시 큐에서 데이터 삭제
        arr_queue_enqueue(*queue, e);     // 기존 큐에 데이터 삽입
    }

    // 메모리 해제
    free(tmp_queue->data); // 임시 큐의 데이터 배열 메모리 해제
    free(tmp_queue);       // 임시 큐 구조체 메모리 해제

    return true;
}

bool arr_queue_create(arr_queue_t **queue) {
    if (queue == NULL) return false; // NULL 포인터인 경우

    *queue = (arr_queue_t *)malloc(sizeof(arr_queue_t)); // 큐 구조체 메모리 할당
    if (*queue == NULL) return false; // 메모리 할당 실패

    // 초기화
    (*queue)->data = NULL; // 데이터 배열 초기화
    (*queue)->size = 0; // 큐의 크기 초기화
    (*queue)->capacity = INIT_CAPACITY; // 큐의 최대 크기 설정
    (*queue)->front = 0; // 큐의 맨 앞 인덱스 초기화
    (*queue)->rear  = 0; // 큐의 맨 뒤 인덱스 초기화

    // 데이터 배열 메모리 할당
    (*queue)->data = (element_t *)malloc(sizeof(element_t) * INIT_CAPACITY);
    if ((*queue)->data == NULL) {  // 메모리 할당 실패
        free(*queue); // 큐 구조체 메모리 해제
        return false;
    }
    
    return true;
}

bool arr_queue_destroy(arr_queue_t **queue) {
    if (queue == NULL) return false; // NULL 포인터인 경우
    if (*queue == NULL) return false; // 이미 해제된 메모리인 경우
    
    if ((*queue)->data != NULL) free((*queue)->data); // 데이터 배열 메모리 해제
    free(*queue); // 큐 구조체 메모리 해제
    *queue = NULL; // 다시 NULL로 초기화 (잘못된 메모리에 접근하기 위함을 방지)

    return true;
}

bool arr_queue_enqueue(arr_queue_t *queue, element_t e) {
    if (queue == NULL) return false; // NULL 포인터인 경우
    if (queue->data == NULL) return false; // 데이터 배열이 NULL인 경우

    // 큐가 가득 찼을 때 용량 증가
    if (queue->size >= queue->capacity) {
        arr_queue_resize(&queue, queue->capacity * 2); // 용량 두 배 증가
    }

    memcpy(&queue->data[queue->rear], &e, sizeof(element_t)); // 데이터 삽입
    queue->rear = (queue->rear + 1) % queue->capacity; // 원형 큐의 맨 뒤 인덱스 업데이트
    queue->size++; // 큐 크기 증가

    return true;
}

bool arr_queue_dequeue(arr_queue_t *queue, element_t *e) {
    if (queue == NULL) return false; // NULL 포인터인 경우
    if (arr_queue_is_empty(queue)) return false; // 큐가 비어있는 경우
    
    if (e != NULL)  // NULL이 아닌 경우에만 데이터 반환 (NULL이면 그냥 삭제만)
        memcpy(e, &queue->data[queue->front], sizeof(element_t)); // 맨 앞 데이터 반환

    queue->front = (queue->front + 1) % queue->capacity; // 원형 큐의 맨 앞 인덱스 업데이트
    queue->size--; // 큐 크기 감소

    // 큐가 1/4 이하로 줄어들었을 때
    if (queue->size > 0 && queue->size == queue->capacity / 4) {
        arr_queue_resize(&queue, queue->capacity / 2); // 용량 절반으로 줄임
    }

    return true;
}

bool arr_queue_peek(arr_queue_t *queue, element_t *e) {
    if (queue == NULL) return false; // NULL 포인터인 경우
    if (arr_queue_is_empty(queue)) return false; // 큐가 비어있는 경우
    
    if (e != NULL)  // NULL이 아닌 경우에만 데이터 반환 (NULL이면 그냥 확인만)
        memcpy(e, &queue->data[queue->front], sizeof(element_t)); // 맨 앞 데이터 반환

    return true;
}

bool arr_queue_is_empty(arr_queue_t *queue) {
    if (queue == NULL) return false; // NULL 포인터인 경우
    return (queue->size == 0); // 큐가 비어있는지 확인
}

int arr_queue_get_size(arr_queue_t *queue) {
    if (queue == NULL) return -1; // NULL 포인터인 경우
    if (queue->data == NULL) return -1; // 데이터 배열이 NULL인 경우
    return queue->size; // 큐의 크기 반환
}