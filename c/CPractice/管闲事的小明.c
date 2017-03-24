#include <stdio.h>
#include <string.h>
int main ()
{
	int n;
	scanf ("%d", &n);
	while (n--)
	{
		int L, M, a[10000];
		memset (a, 0, sizeof(a));
		scanf ("%d%d", &L, &M);
		while (M--)
		{
			int p, q;
			scanf ("%d%d", &p, &q);
			for (int i=p; i <=q; i++)
			{
				a[i] = 1;
			}
		}
		int m = 0;
		for (int i=0; i <= L; i++)
		{
			if (a[i] == 0)
				m++;
		}
		printf ("%d\n", m);
	}
}

