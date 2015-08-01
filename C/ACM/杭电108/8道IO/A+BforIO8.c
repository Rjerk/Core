#include <stdio.h>

int main ()
{
	int n;	
	scanf ("%d", &n);
	while (n--)
	{
		int m, sum = 0, a;
		scanf ("%d", &m);
		for (int i = 0; i < m; i++)
		{
			scanf ("%d", &a);
			sum += a;
		}
		if ( n == 0)
			printf ("%d\n", sum);
		else
			printf ("%d\n\n", sum);
		sum = 0;
	}
	return 0;
}

