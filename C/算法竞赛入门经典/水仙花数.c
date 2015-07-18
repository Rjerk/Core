#include <stdio.h>

int main ()
{
	int num;
	scanf ("%d", &num);
	int a = num % 10;
	int b = num / 10 % 10;
	int c = num / 100;
	if ( num == a*a*a + b*b*b + c*c*c)
		printf ("%d is daffodil\n", num);
	else
		printf ("%d is not\n", num);
}

