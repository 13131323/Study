/*
 * 메모리 저장 위치
*/

#include <stdio.h>

int main(void) {
    char var1[10000000];    // 10MB의 크기를 할당할 수 있는가?
    printf("Success to allocate %ld-bytes memory!\n", sizeof(var1));

    /* powershell에서 gcc 컴파일 시에 스택메모리를 설정하기 위해서는
       "-Wl,--stack,[size]" 옵션을 추가한다.
       ex) gcc -o run.exe source.c "-Wl,--stack,100000000"
           -> source.c 파일을 run.exe로 컴파일하며, 스택메모리를 약 100MB로 설정 */

    return 0;
}