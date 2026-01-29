#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "element.h"
#include "queue_linked.h"

bool linked_queue_create(linked_queue_t **queue) {
    if (queue == NULL) return false; // NULL 포인터인 경우

    *queue = (linked_queue_t *)malloc(sizeof(linked_queue_t)); // 큐 구조체 메모리 할당
    if (*queue == NULL) return false; // 메모리 할당 실패

    // 초기화
    (*queue)->front = NULL; // 큐의 맨 앞 노드 포인터 초기화
    (*queue)->rear = NULL;  // 큐의 맨 뒤 노드 포인터 초기화
    (*queue)->size = 0;     // 큐의 크기 초기화

    return true;
}

bool linked_queue_destroy(linked_queue_t **queue) {
    if (queue == NULL) return false; // NULL 포인터인 경우
    if (*queue == NULL) return false; // 이미 해제된 메모리인 경우

    // 큐가 빌때까지 pop
    while (linked_queue_is_empty(*queue) != true) {
        linked_queue_dequeue(*queue, NULL);
    }

    free(*queue); // 큐 구조체 메모리 해제
    *queue = NULL; // 다시 NULL로 초기화 (잘못된 메모리에 접근하기 위함을 방지)

    return true;
}

bool linked_queue_enqueue(linked_queue_t *queue, element_t e) {
    if (queue == NULL) return false; // NULL 포인터인 경우

    // 새로운 노드 생성
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node == NULL) return false; // 메모리 할당 실패

    memcpy(&new_node->data, &e, sizeof(element_t)); // 데이터 삽입
    new_node->next = NULL; // 새로운 노드의 다음 노드를 NULL로 설정

    if (queue->size == 0) { // 큐가 비어있는 경우
        queue->front = new_node; // 맨 앞 노드를 새로운 노드로 설정
        queue->rear  = new_node; // 맨 뒤를 새로운 노드로 설정
    }
    else {
        queue->rear->next = new_node; // 현재 맨 뒤 노드의 다음 노드를 새로운 노드로 설정
        queue->rear = new_node; // 맨 뒤를 새로운 노드로 설정
    }

    queue->size++; // 큐 크기 증가

    return true;
}

bool linked_queue_dequeue(linked_queue_t *queue, element_t *e) {
    if (queue == NULL) return false; // NULL 포인터인 경우
    if (linked_queue_is_empty(queue)) return false; // 큐가 비어있는 경우

    if (e != NULL)  // NULL이 아닌 경우에만 데이터 반환 (NULL이면 그냥 삭제만)
        memcpy(e, &queue->front->data, sizeof(element_t)); // 데이터 반환

    node_t *del_p = queue->front; // 큐의 맨 앞 노드 저장
    queue->front = queue->front->next; // 큐의 맨 앞을 다음 노드로 설정
    queue->size--; // 큐 크기 감소

    free(del_p); // 삭제된 노드 메모리 해제

    if (queue->size == 0) { // 큐가 비어있는 경우
        queue->rear = NULL; // 맨 뒤 포인터도 NULL로 설정
    }

    return true;
}

bool linked_queue_peek(linked_queue_t *queue, element_t *e) {
    if (queue == NULL) return false; // NULL 포인터인 경우
    if (linked_queue_is_empty(queue)) return false; // 큐가 비어있는 경우

    if (e != NULL)  // NULL이 아닌 경우에만 데이터 반환 (NULL이면 그냥 삭제만)
        memcpy(e, &queue->front->data, sizeof(element_t)); // 데이터 반환

    return true;
}

bool linked_queue_is_empty(linked_queue_t *queue) {
    if (queue == NULL) return false; // NULL 포인터인 경우
    return (queue->size == 0); // 큐가 비어있는지 확인
}

int linked_queue_get_size(linked_queue_t *queue) {
    if (queue == NULL) return -1; // NULL 포인터인 경우
    return queue->size; // 큐의 크기 반환
}