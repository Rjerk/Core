#include <stdio.h>
int main ()
{
	int n;
	scanf ("%d", &n);
	while (n--)
	{
		int a[10];
		for (int i=0; i < 10; i++)
			scanf ("%d", &a[i]);
		int s;
		scanf ("%d", &s);
		int m=0;
		for (int i=0; i < 10; i++)
		{
			if (a[i] <= s + 30)
				m++;
		}
		printf ("%d\n", m);
	}
}

