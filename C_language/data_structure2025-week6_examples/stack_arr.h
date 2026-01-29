#ifndef STACK_ARR_H
#define STACK_ARR_H

#include <stdbool.h>
#include "element.h"

/**** stack 관련 구조체 및 함수 선언 ****/
typedef struct _arr_stack_t {
    int size;              // 스택 원소 개수 (스택의 맨 위 인덱스)
    int capacity;          // 스택의 최대 크기
    element_t *data;       // 스택의 데이터 배열
} arr_stack_t;

#define INIT_CAPACITY 1 // 스택의 초기 용량

/**
 * @brief 새로운 Stack을 생성
 * 
 * 새로운 Stack을 위한 메모리를 할당하고, 해당 스택의 size와 capacity를 초기화
 * 
 * @param[out] list arr_stack_t 구조체에 대한 이중포인터.
 * 
 * @return true  if 성공적으로 스택을 생성한 경우
 * @return false if 메모리 할당에 실패한 경우
 */
bool arr_stack_create(arr_stack_t **stack);

/**
 * @brief Stack을 제거하고 모든 자원을 해제
 * 
 * Stack에 대한 이중 포인터를 받아 Stack 내의 모든 데이터를 삭제
 * 작업이 완료된 후 Stack은 비워지고, 데이터에 사용된 메모리는 해제됨
 * 
 * @param stack 제거할 스택에 대한 이중 포인터.
 * 
 * @return true  if 성공적으로 스택을 제거한 경우
 * @return false if 제거가 실패한 경우 (예: 잘못된 입력 또는 메모리 문제)
 */
bool arr_stack_destroy(arr_stack_t **stack);

/**
 * @brief Stack에 데이터를 삽입
 * 
 * Stack에 데이터를 삽입하고, 스택의 크기를 증가시킴
 * 스택이 가득 찼을 때는 용량을 두 배로 증가시킴 (resizing-array)
 * 
 * @param stack 삽입할 스택에 대한 포인터.
 * @param e 삽입할 데이터.
 * 
 * @return true  if 성공적으로 데이터를 삽입한 경우
 * @return false if 삽입이 실패한 경우 (예: 잘못된 입력 또는 메모리 할당 문제)
 */
bool arr_stack_push(arr_stack_t *stack, element_t e);

/**
 * @brief Stack에서 데이터를 삭제
 * 
 * Stack에서 데이터를 삭제하고, 스택의 크기를 감소시킴
 * 삭제된 데이터는 매개변수로 전달된 포인터를 통해 반환됨
 * 삭제 후 스택의 크기가 용량의 1/4 이하로 줄어들면 용량을 절반으로 줄임
 * 
 * @param stack 삭제할 스택에 대한 포인터.
 * @param e 삭제된 데이터를 담을 변수에 대한 주소.
 * 
 * @return true  if 성공적으로 데이터를 삭제한 경우
 * @return false if 삭제가 실패한 경우 (예: 잘못된 입력 또는 스택이 비어있는 경우)
 */
bool arr_stack_pop(arr_stack_t *stack, element_t *e);

/**
 * @brief Stack의 맨 위 데이터를 확인
 * 
 * Stack의 맨 위 데이터를 확인하고, 스택의 크기는 변경하지 않음
 * 확인된 데이터는 매개변수로 전달된 포인터를 통해 반환됨
 * 
 * @param stack 확인할 스택에 대한 포인터.
 * @param e 확인된 데이터를 담을 변수에 대한 주소.
 * 
 * @return true  if 성공적으로 데이터를 확인한 경우
 * @return false if 확인이 실패한 경우 (예: 잘못된 입력 또는 스택이 비어있는 경우)
 */
bool arr_stack_peek(arr_stack_t *stack, element_t *e);

/**
 * @brief Stack이 비어있는지 확인
 * 
 * Stack이 비어있는지 확인하고, 결과를 반환함
 * 
 * @param stack 확인할 스택에 대한 포인터.
 * 
 * @return true  if 스택이 비어있는 경우
 * @return false if 스택에 데이터가 있는 경우
 */
bool arr_stack_is_empty(arr_stack_t *stack);

/**
 * @brief Stack의 크기를 반환
 * 
 * Stack의 현재 크기를 반환함
 * 
 * @param stack 확인할 스택에 대한 포인터.
 * 
 * @return int 스택의 현재 크기 (실패 시 -1 반환)
 *         (예: 잘못된 입력 또는 스택이 비어있는 경우)
 */
int arr_stack_get_size(arr_stack_t *stack);

#endif // STACK_ARR_H