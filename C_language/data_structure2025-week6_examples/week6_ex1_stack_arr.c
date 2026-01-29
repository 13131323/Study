#include <stdio.h>
#include <stdbool.h>

#include "element.h"
#include "stack_arr.h"

int main(void) {
    arr_stack_t *my_stack = NULL; // 스택 선언
    element_t e; // 임시로 사용할 데이터

    // 스택 생성
    if (!arr_stack_create(&my_stack)) {
        printf("Failed to create stack!\n");
        return 1;
    }

    // Push
    printf("======== Push ========\n");
    for (int i = 0; i < 10; i++) {
        set_element(e, i); // 데이터 설정
        arr_stack_push(my_stack, e); // 스택에 데이터 삽입
        printf("%2dth push:", i+1); // 삽입된 데이터 출력
        print_element(e);
        printf(" (size:%d)\n", arr_stack_get_size(my_stack)); // 스택 크기 출력
    }

    // Pop
    printf("======== Pop ========\n");
    for (int i = 0; i < 8; i++) {
        arr_stack_pop(my_stack, &e); // 맨 위 데이터 삭제
        printf("%2dth  pop:", i+1); // 삭제된 데이터 출력
        print_element(e);
        printf(" (size:%d)\n", arr_stack_get_size(my_stack)); // 스택 크기 출력
    }

    // 스택 소멸 (잊지 말자 free!에 해당)
    arr_stack_destroy(&my_stack);

    return 0;
}