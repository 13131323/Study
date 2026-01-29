/*
 * 헤더파일을 이용하여 리스트의 ADT만을 명시
 */

#include <stdbool.h>

#ifndef _ADT_LIST_H_ // 헤더파일의 중복 포함 방지
#define _ADT_LIST_H_

typedef struct _element_t { // 데이터의 타입을 재정의
    int  value;
    char data[1000];
} element_t;

typedef void* list_t;   // 데이터의 포인터 타입을 재정의

bool list_create(list_t *list);     // 리스트 생성
bool list_destroy(list_t *list);    // 리스트 삭제
bool list_insert(list_t list, element_t e, int index);  // 리스트에 데이터 삽입
bool list_delete(list_t list, int index);       // 리스트에서 데이터 삭제
bool list_is_empty(list_t list);                // 리스트가 비어있는지 확인
int  list_search(list_t list, element_t e);     // 리스트에서 데이터 검색
element_t* list_get(list_t list, int index);         // 리스트에서 데이터 가져오기
int  list_get_size(list_t list);                // 리스트의 데이터 개수 반환

#endif