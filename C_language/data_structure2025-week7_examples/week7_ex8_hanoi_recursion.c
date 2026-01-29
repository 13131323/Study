/*
 * 하노이탑 문제를 재귀적으로 해결하는 프로그램
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void hanoi(int n, char src, char aux, char dst);

int main(int argc, char **argv) {
    // Command line argument 확인
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("n must be positive integers.\n");
        return 1;
    }

    /**** 하노이 탑 문제 해결 ****/
    hanoi(n, 'A', 'B', 'C'); // 하노이 탑 문제 해결

    return 0;
}

void hanoi(int n, char src, char aux, char dst) {
    static int cnt = 0; // 이동 횟수 카운트
    if (n == 1) {
        // 원반이 1개인 경우, 그냥 src에서 dst로 이동
        printf("%2d:Move disk %d from %c to %c\n", ++cnt, n, src, dst);
    } else {
        // 누군가가 n-1개의 원반을 src에서 dst를 보조삼아 aux로 이동
        hanoi(n - 1, src, dst, aux);

        // 나는 n번째 원반을 src에서 dst로 이동
        printf("%2d:Move disk %d from %c to %c\n", ++cnt, n, src, dst);

        // 누군가가 n-1개의 원반을 aux에서 src를 보조삼아 dst로 이동
        hanoi(n - 1, aux, src, dst); // n-1개의 원반을 목적 기둥으로 이동
    }
}