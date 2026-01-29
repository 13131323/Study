/*
 * Recursive Function #3
 * 특정 함수에서 자기 자신과 동일한 이름의 함수를 호출하는 예제
 * '호출하지 !않는(종료)! 시점(조건)'을 정의하여 무한 반복을 피하는 방법
 */

 #include <stdio.h>

 /** 자료구조 수업과는 큰 관련은 없습니다. 운영체제 별로 특정 시간동안 멈추는 함수가 달라 매크로상수와 함수로 정의하는 것입니다. **/
 #if defined(_WIN64) || defined(_WIN32)
     #include <windows.h> // Windows에서는 windows.h 헤더 포함
     #define my_sleep(x) Sleep(x * 1000) // Windows에서는 Sleep 함수 사용
 #elif defined(__APPLE__) ||defined(__MACH__)
     #include <unistd.h> // macOS에서는 unistd.h 헤더 포함
     #define my_sleep(x) sleep(x) // macOS에서는 sleep 함수 사용
 #elif defined(__linux__) || defined(__linux)
     #include <unistd.h> // Linux에서는 unistd.h 헤더 포함
     #define my_sleep(x) sleep(x) // Linux에서는 sleep 함수 사용
 #elif defined(__unix__) || defined(__unix)
     #include <unistd.h> // Unix에서는 unistd.h 헤더 포함
     #define my_sleep(x) sleep(x) // Unix에서는 sleep 함수 사용
 #endif
 
 
 void func2(int cnt) {
     printf("func2 called (%dth)\n", cnt);

     if (cnt == 0) { // 종료 조건: cnt가 0일 때
        printf("func2 finished (%dth)\n", cnt);
        return; // 종료
    }
    my_sleep(0.5); // 잠깐 대기 (너무 빠르게 출력되면 보기 힘드니...)
    func2(cnt - 1); // func2에서 func'2'를 호출 (재귀 호출)

    printf("func2 finished (%dth)\n", cnt);
 }
 
 int main(void) {
     printf(" main called\n");
 
     func2(10); // main에서 func2를 호출
 
     printf(" main finished\n");
 
     return 0;
 }