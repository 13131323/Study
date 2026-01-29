/*
 * 포인터 변수의 초기화
 */

#include <stdio.h>

int main(void) {
    /*
      실제로 포인터 변수를 초기화하지 않고 사용하는 것은 매우 위험하니,
      예제로만 이해하고 실전에서는 절!대!로! 하지 마세요.
    */ 
    int *p_int; short *p_short; char *p_char;

    printf("p_int:%p\n", p_int);      // ???? 무슨 값인지 예측 불가
    printf("p_short:%p\n", p_short);  // ???? 무슨 값인지 예측 불가
    printf("p_char:%p\n", p_char);    // ???? 무슨 값인지 예측 불가

    /*
     사용하려고 선언은 했는데, 지금 당장 딱히 값을 넣지 않을거면
     항상 NULL로 초기화 하는 습관이
     매우매우매우매우매우매우매우매우매우매우매우매우매우매우매우매우매우매우매우매우
     중요합니다.
    */
    p_int = NULL;

    /*
      이후에 포인터의 값이 NULL인지 아닌지를 체크하며,
      NULL이 아니면 어떤 특정 주소가 담겨있다는 뜻이니까
      그때 접근하는 습관이 좋습니다.
    */
    if (p_int != NULL)
        printf("do something\n");

    return 0;
}
