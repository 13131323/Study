/*
 * 특정 수행작업의 수행속도를 측정하는 방법
 */

#include <stdio.h>
#include <time.h>

int main(void) {
    // 시간 측정을 위한 변수 (시작, 끝에 시간을 측정한 뒤 차이로 수행시간을 구한다!)
    clock_t start, end;

    unsigned long long int i;
    unsigned long long int cnt = 0;
    start = clock();    // 시간 측정 시작

    for (i = 0; i < 1000000; i++) { // 특정 횟수만큼 반복
        cnt++;
    }

    end = clock();  // 시간 측정 종료

    // 수행시간 출력
    printf("Elapsed time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}