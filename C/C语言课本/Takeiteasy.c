#include <stdio.h>

int main ()
{
	int n;
	while (scanf("%d", &n) != EOF)
	{
		int a[10], m=0;
		for (int i=0; i < 10; i++)
			scanf ("%d", &a[i]);
		for (int i=0; i < 10; i++)
		{
			if (n == 0)
				break;
			n += a[i];
			m ++;
		}
		printf ("%d\n", m);
	}
	return 0;
}

