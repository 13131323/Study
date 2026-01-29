/*
 * 메모리 관련 함수 (realloc)
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 만약 현재까지 읽은 숫자의 개수가 5개를 넘어가면
 * 메모리를 다시 할당하면 되지 않을까?
 */
int main(void) {
    int i, cnt = 0;
    int *malloc_p = (int *)malloc(5 * sizeof(int));
    char buf[256]; // 파일에서 읽은 값을 저장할 버퍼
    FILE *fp;

    // inputs폴더의 input01.txt 파일을 읽기 모드로 열기
    if ((fp = fopen("inputs/input01.txt", "r")) == NULL) {
        printf("Failed to open file\n");
        return 1;
    }
    printf("Success to open file\n");

    while (fgets(buf, sizeof(buf), fp) != NULL) {   // 파일에서 한 줄씩 읽어서 buf에 저장
        if (cnt >= sizeof(malloc_p) / sizeof(int)) { // 배열의 크기를 채우면
            printf("realloc at %dth index\n", cnt);
            // 메모리를 다시 할당하면 되지 않을까?
            malloc_p = (int *)realloc(malloc_p, (cnt + 1) * sizeof(int));
        }
        malloc_p[cnt] = (int)strtol(buf, NULL, 10); // 문자열을 정수로 변환하여 malloc_p에 저장
        cnt++;
    }
    printf("Read %d integers\n", cnt);

    // 잊지말자 fclose!!
    if (fclose(fp) == EOF) {
        printf("Failed to close file\n");
        return 1;
    }
    printf("Success to close file\n");
    
    // 파일에서 읽은 값을 출력
    for (i = 0; i < cnt; i++)
        printf("malloc_p[%d]: %d\n", i, malloc_p[i]);

    // 잊지말자 free!!
    free(malloc_p);

    return 0;
}
