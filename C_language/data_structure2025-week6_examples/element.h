#ifndef ELEMENT_H
#define ELEMENT_H

#include <stdio.h>

typedef struct _element_t {
    int data;
} element_t; // 데이터 타입 정의
 // 데이터 설정 매크로 함수
#define set_element(e, d) do { (e).data = (d); } while(0)
 // 데이터 출력 매크로 함수
#define print_element(e) do { printf("%3d", (e).data); } while(0)

#endif // ELEMENT_H