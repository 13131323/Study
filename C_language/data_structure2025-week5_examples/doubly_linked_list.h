#include <stdbool.h>
#include "element.h"

/**** Linked List ****/
typedef struct _d_ll_node_t {
    element_t element;         // 데이터
    struct _d_ll_node_t *next;   // 다음 노드(아이템)의 주소
    struct _d_ll_node_t *prev;   // 이전 노드(아이템)의 주소
} d_ll_node_t;
 
typedef struct _d_linked_list_t {
    int size;          // 저장하고 있는 데이터의 개수
    struct _d_ll_node_t *head;    // 첫 번째 노드(아이템)의 주소
    struct _d_ll_node_t *tail;    // 마지막 노드(아이템)의 주소
} d_linked_list_t;
 
/* 함수 원형 */
// create / destroy
bool d_linked_list_create  (d_linked_list_t **list);
bool d_linked_list_destroy (d_linked_list_t **list);
// insert
bool d_linked_list_insert_first (d_linked_list_t *list, element_t e);
bool d_linked_list_insert_last  (d_linked_list_t *list, element_t e);
bool d_linked_list_insert_index (d_linked_list_t *list, element_t e, int index);
// delete
bool d_linked_list_delete_first (d_linked_list_t *list);
bool d_linked_list_delete_last  (d_linked_list_t *list);
bool d_linked_list_delete_index (d_linked_list_t *list, int index);
// search
int d_linked_list_search_by_value (d_linked_list_t *list, element_t e);
element_t* d_linked_list_search_by_index (d_linked_list_t *list, int index);
// statistics
int d_linked_list_get_size (d_linked_list_t *list);