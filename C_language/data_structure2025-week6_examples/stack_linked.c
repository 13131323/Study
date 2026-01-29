#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "element.h"
#include "stack_linked.h"

bool linked_stack_create(linked_stack_t **stack) {
    if (stack == NULL) return false; // NULL 포인터인 경우

    *stack = (linked_stack_t *)malloc(sizeof(linked_stack_t)); // 스택 구조체 메모리 할당
    if (*stack == NULL) return false; // 메모리 할당 실패

    // 초기화
    (*stack)->top = NULL; // 스택의 맨 위 노드 포인터 초기화
    (*stack)->size = 0; // 스택의 크기 초기화

    return true;
}

bool linked_stack_destroy(linked_stack_t **stack) {
    if (stack == NULL) return false; // NULL 포인터인 경우
    if (*stack == NULL) return false; // 이미 해제된 메모리인 경우

    // 스택이 빌때까지 pop
    while (linked_stack_is_empty(*stack) != true) {
        linked_stack_pop(*stack, NULL);
    }

    free(*stack); // 스택 구조체 메모리 해제
    *stack = NULL; // 다시 NULL로 초기화 (잘못된 메모리에 접근하기 위함을 방지)

    return true;
}

bool linked_stack_push(linked_stack_t *stack, element_t e) {
    if (stack == NULL) return false; // NULL 포인터인 경우

    // 새로운 노드 생성
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node == NULL) return false; // 메모리 할당 실패

    memcpy(&new_node->data, &e, sizeof(element_t)); // 데이터 삽입

    /** singly linked list의 insert first와 동일하게 **/
    new_node->next = stack->top; // 새로운 노드의 다음 노드를 현재 스택의 맨 위로 설정
    stack->top = new_node;       // 스택의 맨 위를 새로운 노드로 설정
    stack->size++; // 스택 크기 증가

    return true;
}

bool linked_stack_pop(linked_stack_t *stack, element_t *e) {
    if (stack == NULL) return false; // NULL 포인터인 경우
    if (linked_stack_is_empty(stack)) return false; // 스택이 비어있는 경우

    if (e != NULL)  // NULL이 아닌 경우에만 데이터 반환 (NULL이면 그냥 삭제만)
        memcpy(e, &stack->top->data, sizeof(element_t)); // 데이터 반환

    node_t *del_p = stack->top; // 스택의 맨 위 노드 저장
    stack->top = stack->top->next; // 스택의 맨 위를 다음 노드로 설정
    stack->size--; // 스택 크기 감소

    free(del_p); // 노드 메모리 해제

    return true;
}

bool linked_stack_peek(linked_stack_t *stack, element_t *e) {
    if (stack == NULL) return false; // NULL 포인터인 경우
    if (linked_stack_is_empty(stack)) return false; // 스택이 비어있는 경우

    if (e != NULL)  // NULL이 아닌 경우에만 데이터 반환 (NULL이면 그냥 삭제만)
        memcpy(e, &stack->top->data, sizeof(element_t)); // 데이터 반환

    return true;
}

bool linked_stack_is_empty(linked_stack_t *stack) {
    if (stack == NULL) return false; // NULL 포인터인 경우
    return (stack->size == 0); // 스택이 비어있는지 확인
}

int linked_stack_get_size(linked_stack_t *stack) {
    if (stack == NULL) return -1; // NULL 포인터인 경우
    return stack->size; // 스택의 크기 반환
}