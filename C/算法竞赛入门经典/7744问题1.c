#include <stdio.h>

int main ()
{
	for (int i=33; (i*i <= 9999) && (i*i >= 1000); i++)
	{
		int n = i * i;
		if ( n/1000 == n/100%10 && n%10 == n/10%10)
			printf ("%d\n", n);
	}
	return 0;
}

