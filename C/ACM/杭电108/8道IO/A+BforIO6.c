#include <stdio.h>

int main ()
{
	int n, sum = 0, a;
	while (scanf ("%d", &n) != EOF)
	{
		for (int i = 0; i < n; i++)
		{
			scanf ("%d", &a);
			sum += a;
		}
		printf ("%d\n", sum);
		sum = 0;
	}
	return 0;
}

