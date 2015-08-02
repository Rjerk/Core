#include <stdio.h>

int main () 
{
	int n;
	scanf ("%d", &n);
	while (n--)
	{
		int sum = 0, a, m;
		scanf ("%d", &m);
		for (int i = 0; i < m; i++)
		{
			scanf ("%d", &a);
			sum += a;
		}
		printf ("%d\n", sum);
		sum = 0;
	}
	return 0;
}

