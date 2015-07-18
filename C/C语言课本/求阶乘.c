#include <stdio.h>

int main ()
{
	int n;
	scanf ("%d", &n);
	while (n--)
	{
		int m;
		scanf ("%d", &m);
		int sum = 1;
		for (int i=1; i <= m; i++)
		{
				sum *= i;
		}
		printf ("%d 的阶乘为%d\n", m, sum);
	}
}

