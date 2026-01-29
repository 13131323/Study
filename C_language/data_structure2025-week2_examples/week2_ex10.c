/*
 * 포인터 배열의 활용 #3
 */


#include <stdio.h>

int main(void) {
    int i;
    // 2차원 배열 선언
    int score[2][3] = {{0x30, 0x44, 0x67}, {0x87, 0x43}};

    /*
     배열[i]의 이름은 시작 원소의 주소, 따라서 포인터 변수에 할당 가능
     따라서 포인터배열의 원소에 배열의 이름을 할당할 수 있다.
    */
    int *p_arr[2] = { score[0], score[1] };

    int **pp_arr = p_arr;

    // p_arr[0]은? score[0]의 값 == score[0][0~1]의 시작주소
    printf("p_arr[0]:%p, score[0]:%p\n", pp_arr[0], score[0]);

    // p_arr[0][i]는? p_arr[0] 쓰여진 주소(score[0])에서 i번째 원소의 값 == score[0][i]
    for (i = 0; i < 3; i++)
        printf("p_arr[0][%d]:%x, score[0][%d]:%x\n", i, pp_arr[0][i], i, score[0][i]);

    // p_arr[1]은? score[1]의 값 == score[1][0~1]의 시작주소
    printf("p_arr[1]:%p, score[1]:%p\n", pp_arr[1], score[1]);

    // p_arr[1][i]는? p_arr[1] 쓰여진 주소(score[1])에서 i번째 원소의 값 == score[1][i]
    for (i = 0; i < 3; i++)
        printf("p_arr[1][%d]:%x, score[1][%d]:%x\n", i, pp_arr[1][i], i, score[1][i]);
    
    return 0;
}