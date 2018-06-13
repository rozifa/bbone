#include <stdio.h>

//thanks fred

int main(){

	static int a = 4;
	static int b = a;
	printf("%d\n", a);
	printf("%d\n", b);

	return 0;
}
