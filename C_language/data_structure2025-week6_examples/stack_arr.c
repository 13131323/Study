#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "element.h"
#include "stack_arr.h"

bool arr_stack_create(arr_stack_t **stack) {
    if (stack == NULL) return false; // NULL 포인터인 경우

    *stack = (arr_stack_t *)malloc(sizeof(arr_stack_t)); // 스택 구조체 메모리 할당
    if (*stack == NULL) return false; // 메모리 할당 실패

    // 초기화
    (*stack)->data = NULL; // 데이터 배열 초기화
    (*stack)->size = 0; // 스택의 크기 초기화
    (*stack)->capacity = INIT_CAPACITY; // 스택의 최대 크기 설정

    // 데이터 배열 메모리 할당
    (*stack)->data = (element_t *)malloc(sizeof(element_t) * INIT_CAPACITY);
    if ((*stack)->data == NULL) {  // 메모리 할당 실패
        free(*stack); // 스택 구조체 메모리 해제
        return false;
    }
    return true;
}

bool arr_stack_destroy(arr_stack_t **stack) {
    if (stack == NULL) return false;
    if ((*stack) == NULL) return false;

    if((*stack)->data != NULL) free((*stack)->data);
    free(*stack);
    *stack = NULL;
    return true;
}

bool arr_stack_push(arr_stack_t *stack, element_t e) {
    if (stack == NULL) return false; // NULL 포인터인 경우
    if (stack->data == NULL) return false; // 데이터 배열이 NULL인 경우

    // 스택이 가득 찼을 때 용량 증가
    if (stack->size >= stack->capacity) {
        stack->capacity *= 2; // 용량 두 배 증가
        stack->data = (element_t *)realloc(stack->data, sizeof(element_t) * stack->capacity); // 메모리 재할당
        if (stack->data == NULL) return false; // 메모리 재할당 실패
    }

    memcpy(&stack->data[stack->size], &e, sizeof(element_t)); // 데이터 삽입
    stack->size++; // 스택 크기 증가

    return true;
}

bool arr_stack_pop(arr_stack_t *stack, element_t *e) {
    if (stack == NULL) return false; // NULL 포인터인 경우
    if (arr_stack_is_empty(stack)) return false; // 스택이 비어있는 경우
    
    if (e != NULL)  // NULL이 아닌 경우에만 데이터 반환 (NULL이면 그냥 삭제만)
        memcpy(e, &stack->data[stack->size - 1], sizeof(element_t)); // 맨 위 데이터 반환

    stack->size--; // 스택 크기 감소
    // 스택이 1/4 이하로 줄어들었을 때
    if (stack->size > 0 && stack->size == stack->capacity / 4) {
        stack->capacity /= 2; // 절반
        stack->data = (element_t *)realloc(stack->data, sizeof(element_t) * stack->capacity);
        if (stack->data == NULL) return false; // 메모리 재할당 실패
    }

    return true;
}

bool arr_stack_peek(arr_stack_t *stack, element_t *e) {
    if (stack == NULL) return false; // NULL 포인터인 경우
    if (arr_stack_is_empty(stack)) return false; // 스택이 비어있는 경우

    if (e != NULL)  // NULL이 아닌 경우에만 데이터 반환 (NULL이면 그냥 삭제만)
        memcpy(e, &stack->data[stack->size - 1], sizeof(element_t)); // 맨 위 데이터 반환

    return true;
}

bool arr_stack_is_empty(arr_stack_t *stack) {
    if (stack == NULL) return true; // NULL 포인터인 경우
    if (stack->data == NULL) return true; // 데이터 배열이 NULL인 경우
    return stack->size == 0; // 스택이 비어있는지 여부 반환
}

int arr_stack_get_size(arr_stack_t *stack) {
    if (stack == NULL) return -1; // NULL 포인터인 경우
    if (stack->data == NULL) return -1; // 데이터 배열이 NULL인 경우
    return stack->size; // 스택의 크기 반환
}