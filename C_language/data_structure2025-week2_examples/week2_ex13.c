/*
 * C언어 표준 버전 확인
 */

#include <stdio.h>

int main() {
    /* gcc -o [실행파일이름] [소스파일이름] -std=[c버전]으로 표준을 지정할 수 있다.*/

    /* __STDC_VERSION__에는 현재 사용중인 C언어 표준 버전이 저장되어 있다. (c99부터) */
    /*
        c99 = 199901
        c11 = 201112
        c17 = 201710
    */
    printf("__STDC_VERSION__: %ld\n", __STDC_VERSION__);

    return 0;
}