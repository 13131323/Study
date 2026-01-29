#include <stdio.h>
#include "../StaticLib1/MyFunc.h"
int main(void)
{
	int a = 10;
	int b = 2;
	printf_s("if x = %d and y = %d, 2x+4y-8 = %d\n", a, b, Func(a, b));
	// system("pause");
	return 0;
}