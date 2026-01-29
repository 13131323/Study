/*
 * 등차수열의 합을 재귀적으로 계산하는 프로그램
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef unsigned long long int ull; // 매우 큰 양의 정수를 담기 위해 unsigned long long int를 사용 (기니까 줄여서 ull로 typedef)

ull arithmetic_sum(ull n, ull a, ull d); // 함수 원형 선언

int main(int argc, char **argv) {
    // Command line argument 확인
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <n> <a> <d>\n", argv[0]);
        return 1;
    }
    ull n = strtoull(argv[1], NULL, 10); // n: 항의 개수
    ull a = strtoull(argv[2], NULL, 10); // a: 첫 번째 항
    ull d = strtoull(argv[3], NULL, 10); // d: 공차
    
    if (n <= 0) {
        printf("n must be positive integers.\n");
        return 1;
    }
    // 시간 측정을 위한 변수
    clock_t start, end; double elapsed_time = 0.0;
    ull repeat = 0;

    ull sum = 0; // 등차수열의 합 초기화
    start = clock(); // 시작 시간 측정
    do {
        repeat++;
        end = clock(); // 종료 시간 측정
        sum = arithmetic_sum(n, a, d); // 등차수열의 합 계산
        elapsed_time = (double)(end - start) / CLOCKS_PER_SEC; // 경과 시간 계산
    } while (elapsed_time < 1); // 1초 이상 경과할 때까지 반복

    printf("Sum of the arithmetic sequence: %llu\n", sum); // 결과 출력
    printf("Elapsed time: %.8f seconds (%llu times)\n", elapsed_time/repeat, repeat); // 경과 시간 출력

    return 0;
}

ull arithmetic_sum(ull n, ull a, ull d) {
    if (n == 1) return a; // 종료 조건: n이 1일 때 첫 번째 항 반환
    else return a + arithmetic_sum(n - 1, a + d, d); // 재귀 호출
}