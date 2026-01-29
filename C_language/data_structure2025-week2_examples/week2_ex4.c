/*
 * 2차원배열 vs 2중포인터
 */

#include <stdio.h>

int main(void) {
    int score[2][3] = {{30, 44, 67}, 
                       {87, 43}}; 
    int **arr_p = (int **)score;

    // 2차원 배열의 인덱스로 접근?
    printf("score[0][0]:%d\n", score[0][0]);
    printf("score[1][2]:%d\n", score[1][2]);

    // 2중포인터로 접근?
    printf("arr_p[0][0]:%d\n", arr_p[0][0]);
    printf("arr_p[1][2]:%d\n", arr_p[1][2]);

    return 0;
}