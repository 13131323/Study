/*
 * 메모리 관련 함수 (memset)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int i;
    int *p = (int *)malloc(5 * sizeof(int));

    // 초기화를 하지 않고 출력하면 쓰레기값(dummy value)이 출력된다.
    for (i = 0; i < 5; i++) printf("p[%d]:0x%02X\n", i, p[i]);

    // memset 함수를 사용하여 0으로 초기화
    memset(p, 0, 5 * sizeof(int));  // 5 * sizeof(int)만큼의 메모리를 0으로 초기화
    printf("memset to 0\n");
    for (i = 0; i < 5; i++) printf("p[%d]:0x%02X\n", i, p[i]);

    // memset 함수를 사용하여 0x12로 초기화
    memset(p, 0x12, 5 * sizeof(int));
    printf("memset to 0x12\n");
    for (i = 0; i < 5; i++) printf("p[%d]:0x%02X\n", i, p[i]);

    // 잊지 말자 free!!
    free(p);

    return 0;
}
