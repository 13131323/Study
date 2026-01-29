/*
 * 팩토리얼을 재귀적으로 계산하는 프로그램
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 매우 큰 양의 정수를 담기 위해 unsigned long long int를 사용 (기니까 줄여서 ull로 typedef)
typedef unsigned long long int ull;

ull fact(int n) {
    if (n == 1) return n;   // 종료조건: 1! = 1 (base case)
    else        return n * fact(n - 1); // n! = n * (n-1)!
}

int main(int argc, char **argv) {
    clock_t start, end; // 시간 측정을 위한 변수
    ull ret;

    // command line argument 검사
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        printf("      n: non-negative integer\n");
        return 1;
    }

    // n검사
    int n = atoi(argv[1]); // 문자열을 정수로 변환
    if (n < 0) {
        printf("Error: n must be a non-negative integer.\n");
        return 1;
    }

    start = clock(); // 시작 시간 측정
    ret = fact(n); // 팩토리얼 계산
    end = clock(); // 종료 시간 측정

    printf("Factorial(%d) = %llu\n", n, ret); // F(n) 출력
    printf("Elapsed time: %.3f seconds\n", (double)(end - start) / CLOCKS_PER_SEC); // 경과 시간 출력
    return 0;
}