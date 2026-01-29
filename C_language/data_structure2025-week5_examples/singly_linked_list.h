#include <stdbool.h>
#include "element.h"

/**** Linked List ****/
typedef struct _s_ll_node_t {
    element_t element;         // 데이터
    struct _s_ll_node_t *next;   // 다음 노드(아이템)의 주소
} s_ll_node_t;
 
typedef struct _s_linked_list_t {
    int size;          // 저장하고 있는 데이터의 개수
    struct _s_ll_node_t *head;    // 첫 번째 노드(아이템)의 주소
} s_linked_list_t;

/* 함수 원형 */
// create / destroy
bool s_linked_list_create  (s_linked_list_t **list);
bool s_linked_list_destroy (s_linked_list_t **list);
// insert
bool s_linked_list_insert_first (s_linked_list_t *list, element_t e);
bool s_linked_list_insert_last  (s_linked_list_t *list, element_t e);
bool s_linked_list_insert_index (s_linked_list_t *list, element_t e, int index);
// delete
bool s_linked_list_delete_first (s_linked_list_t *list);
bool s_linked_list_delete_last  (s_linked_list_t *list);
bool s_linked_list_delete_index (s_linked_list_t *list, int index);
// search
int s_linked_list_search_by_value (s_linked_list_t *list, element_t e);
element_t* s_linked_list_search_by_index (s_linked_list_t *list, int index);
// statistics
int s_linked_list_get_size (s_linked_list_t *list);