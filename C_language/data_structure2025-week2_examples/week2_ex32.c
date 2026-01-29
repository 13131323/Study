/*
 * 메모리 관련 함수 (malloc + free -> malloc)
 */

#include <stdio.h>
#include <stdlib.h>

/* 파일의 내용을 계속해서 추가하고 싶은데...
 * 파일의 내용이 몇개인지 사전에 알지 못한다...
 */
int main(void) {
    int i, cnt = 0; // 인덱스 0으로 초기화
    int *malloc_p = (int *)malloc(5 * sizeof(int)); // 4바이트 정수 데이터를 5개 저장할 수 있는 동적 메모리를 할당
    char buf[256]; // 파일에서 읽은 값을 저장할 버퍼
    FILE *fp;

    // inputs폴더의 input01.txt 파일을 읽기 모드로 열기
    if ((fp = fopen("inputs/input01.txt", "r")) == NULL) {
        printf("Failed to open file\n");
        return 1;
    }
    printf("Success to open file\n");

    while (fgets(buf, sizeof(buf), fp) != NULL) { // 파일에서 한 줄씩 읽어서 buf에 저장
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
