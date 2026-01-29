/*
 * 2차원배열의 이름?
 */

#include <stdio.h>

int main(void) {
    int score[2][3] = {{30, 44, 67}, 
                       {87, 43, 0}}; 

    // 2차원 배열의 이름은?
    printf("score:%p\n", score);

    // 1번 접근했을 때?
    printf("score[0]:%p\n", score[0]);
    printf("score[1]:%p\n", score[1]);

    return 0;
}