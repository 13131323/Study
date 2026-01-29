#include <stdio.h>
#include <stdbool.h>

#include "element.h"
#include "queue_arr.h"

int main(void) {
    arr_queue_t *my_queue = NULL; // 큐 선언
    element_t e; // 임시로 사용할 데이터

    // 큐 생성
    if (!arr_queue_create(&my_queue)) {
        printf("Failed to create queue!\n");
        return 1;
    }

    // Enqueue
    printf("======== Enqueue ========\n");
    for (int i = 0; i < 10; i++) {
        set_element(e, i); // 데이터 설정
        arr_queue_enqueue(my_queue, e); // 큐에 데이터 삽입
        printf("%2dth enqueue:", i+1); // 삽입된 데이터 출력
        print_element(e);
        printf(" (size:%d)\n", arr_queue_get_size(my_queue)); // 큐 크기 출력
    }

    // Dequeue
    printf("======== Dequeue ========\n");
    for (int i = 0; i < 8; i++) {
        arr_queue_dequeue(my_queue, &e); // 맨 앞 데이터 삭제
        printf("%2dth dequeue:", i+1); // 삭제된 데이터 출력
        print_element(e);
        printf(" (size:%d)\n", arr_queue_get_size(my_queue)); // 큐 크기 출력
    }

    // 큐 소멸 (잊지 말자 free!에 해당)
    arr_queue_destroy(&my_queue);

    return 0;
}