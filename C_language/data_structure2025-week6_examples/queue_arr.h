#ifndef QUEUE_ARR_H
#define QUEUE_ARR_H

#include <stdbool.h>
#include "element.h"

/**** queue 관련 구조체 및 함수 선언 ****/
typedef struct _arr_queue_t {
    int size;             // 큐 원소 개수
    int capacity;         // 큐의 최대 크기
    int front;            // 큐의 맨 앞 인덱스
    int rear;             // 큐의 맨 뒤 인덱스
    element_t *data;      // 큐의 데이터 배열
} arr_queue_t;

#define INIT_CAPACITY 1 // 큐의 초기 용량

/**
 * @brief 새로운 queue를 생성
 * 
 * 새로운 queue를 위한 메모리를 할당하고, 해당 큐의 size와 capacity를 초기화
 * 
 * @param[out] list arr_queue_t 구조체에 대한 이중포인터.
 * 
 * @return true  if 성공적으로 큐를 생성한 경우
 * @return false if 메모리 할당에 실패한 경우
 */
bool arr_queue_create(arr_queue_t **queue);

/**
 * @brief queue를 제거하고 모든 자원을 해제
 * 
 * queue에 대한 이중 포인터를 받아 queue 내의 모든 데이터를 삭제
 * 작업이 완료된 후 queue은 비워지고, 데이터에 사용된 메모리는 해제됨
 * 
 * @param queue 제거할 큐에 대한 이중 포인터.
 * 
 * @return true  if 성공적으로 큐를 제거한 경우
 * @return false if 제거가 실패한 경우 (예: 잘못된 입력 또는 메모리 문제)
 */
bool arr_queue_destroy(arr_queue_t **queue);

/**
 * @brief queue에 데이터를 삽입
 * 
 * queue에 데이터를 삽입하고, 큐의 크기를 증가시킴
 * 큐가 가득 찼을 때는 용량을 두 배로 증가시킴 (resizing-array)
 * 
 * @param queue 삽입할 큐에 대한 포인터.
 * @param e 삽입할 데이터.
 * 
 * @return true  if 성공적으로 데이터를 삽입한 경우
 * @return false if 삽입이 실패한 경우 (예: 잘못된 입력 또는 메모리 할당 문제)
 */
bool arr_queue_enqueue(arr_queue_t *queue, element_t e);

/**
 * @brief queue에서 데이터를 삭제
 * 
 * queue에서 데이터를 삭제하고, 큐의 크기를 감소시킴
 * 삭제된 데이터는 매개변수로 전달된 포인터를 통해 반환됨
 * 삭제 후 큐의 크기가 용량의 1/4 이하로 줄어들면 용량을 절반으로 줄임
 * 
 * @param queue 삭제할 큐에 대한 포인터.
 * @param e 삭제된 데이터를 담을 변수에 대한 주소.
 * 
 * @return true  if 성공적으로 데이터를 삭제한 경우
 * @return false if 삭제가 실패한 경우 (예: 잘못된 입력 또는 큐가 비어있는 경우)
 */
bool arr_queue_dequeue(arr_queue_t *queue, element_t *e);

/**
 * @brief queue의 맨 위 데이터를 확인
 * 
 * queue의 맨 위 데이터를 확인하고, 큐의 크기는 변경하지 않음
 * 확인된 데이터는 매개변수로 전달된 포인터를 통해 반환됨
 * 
 * @param queue 확인할 큐에 대한 포인터.
 * @param e 확인된 데이터를 담을 변수에 대한 주소.
 * 
 * @return true  if 성공적으로 데이터를 확인한 경우
 * @return false if 확인이 실패한 경우 (예: 잘못된 입력 또는 큐가 비어있는 경우)
 */
bool arr_queue_peek(arr_queue_t *queue, element_t *e);

/**
 * @brief queue이 비어있는지 확인
 * 
 * queue이 비어있는지 확인하고, 결과를 반환함
 * 
 * @param queue 확인할 큐에 대한 포인터.
 * 
 * @return true  if 큐가 비어있는 경우
 * @return false if 큐에 데이터가 있는 경우
 */
bool arr_queue_is_empty(arr_queue_t *queue);

/**
 * @brief queue의 크기를 반환
 * 
 * queue의 현재 크기를 반환함
 * 
 * @param queue 확인할 큐에 대한 포인터.
 * 
 * @return int 큐의 현재 크기 (실패 시 -1 반환)
 *         (예: 잘못된 입력 또는 큐가 비어있는 경우)
 */
int arr_queue_get_size(arr_queue_t *queue);

#endif // QUEUE_ARR_H