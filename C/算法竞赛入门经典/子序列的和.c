#include <stdio.h>

int main ()
{
	int n, m;
	int a=1;
	while ( scanf("%d%d", &n, &m), n!=0 && m!=0)
	{
		float sum = 0;
		for (int i=n; i <= m; i++)
		{
			sum += 1.0/i/i;
			printf ("1/(%d*%d)+", i, i);
		}
		printf ("case %d : %.5f\n", a, sum);
		a++;
	}
}

