#include <stdio.h>
#include <stdbool.h>

#include "element.h"
#include "queue_linked.h"

int main(void) {
    linked_queue_t *my_queue = NULL; // 큐 선언
    element_t e; // 임시로 사용할 데이터

    // 큐 생성
    if (!linked_queue_create(&my_queue)) {
        printf("Failed to create queue!\n");
        return 1;
    }

    // Enqueue
    printf("======== Enqueue ========\n");
    for (int i = 0; i < 10; i++) {
        set_element(e, i); // 데이터 설정
        linked_queue_enqueue(my_queue, e); // 큐에 데이터 삽입
        printf("%2dth enqueue:", i+1); // 삽입된 데이터 출력
        print_element(e);
        printf(" (size:%d)\n", linked_queue_get_size(my_queue)); // 큐 크기 출력
    }

    // Dequeue
    printf("======== Dequeue ========\n");
    for (int i = 0; i < 8; i++) {
        linked_queue_dequeue(my_queue, &e); // 맨 앞 데이터 삭제
        printf("%2dth dequeue:", i+1); // 삭제된 데이터 출력
        print_element(e);
        printf(" (size:%d)\n", linked_queue_get_size(my_queue)); // 큐 크기 출력
    }

    // 큐 소멸 (잊지 말자 free!에 해당)
    linked_queue_destroy(&my_queue);

    return 0;
}