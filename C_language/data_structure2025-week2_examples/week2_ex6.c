/*
 * 2차원배열 vs 2중포인터
 */

#include <stdio.h>

int main(void) {
    int score[2][3] = {{0x30, 0x44, 0x67}, {0x87, 0x43}}; 
    int **arr_p = (int **)score;

    // arr_p[0]의 값은?
    printf("arr_p[0]:%p\n", arr_p[0]);
    printf("score[0]:%p\n", score[0]);

    return 0;
}