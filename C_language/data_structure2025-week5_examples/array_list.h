#include <stdbool.h>
#include "element.h"

/**** Array List  ****/
typedef struct {
    element_t *data; // 데이터를 저장할 배열
    int capacity;    // 배열의 용량
    int size;        // 배열에 저장된 데이터의 개수
} array_list_t;

/* 함수 원형 */
// create / destroy
bool array_list_create  (array_list_t **list);
bool array_list_destroy (array_list_t **list);
// insert
bool array_list_insert_first (array_list_t *list, element_t e);
bool array_list_insert_last  (array_list_t *list, element_t e);
bool array_list_insert_index (array_list_t *list, element_t e, int index);
// delete
bool array_list_delete_first (array_list_t *list);
bool array_list_delete_last  (array_list_t *list);
bool array_list_delete_index (array_list_t *list, int index);
// search
int        array_list_search_by_value (array_list_t *list, element_t e);
element_t* array_list_search_by_index (array_list_t *list, int index);
// statistics
int array_list_get_size (array_list_t *list);