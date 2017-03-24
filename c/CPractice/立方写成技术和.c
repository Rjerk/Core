#include <stdio.h>

int main ()
{	
	int n;
	scanf ("%d", &n);
	int  sum, i, j, k;
	k = n * n * n;
	for (i = 1; i < k/2; i+=2)
	{
		for (j = i, sum = 0; sum < k; j += 2)
			sum += j;
		if (sum == k)
			printf ("%d * %d * %d = %d = from %d to %d\n", n, n, n, sum, i, j-2);
	}
}

