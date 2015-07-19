#include <stdio.h>
#include <string.h>
#define maxn 100

int a[maxn][maxn];

int main ()
{
	int x, y, tot = 0, n;
	memset (a, 0, sizeof(a));
	scanf ("%d", &n);
	tot = a[x=0][y=n-1] = 1;
	while (tot < n*n)
	{
		while (x < n-1 && !a[x+1][y])	a[++x][y] = ++tot;
		while (y >= 1  && !a[x][y-1])   a[x][--y] = ++tot;
		while (x >= 1  && !a[x-1][y])   a[--x][y] = ++tot;
		while (x < n-1 && !a[x][y+1])   a[x][++y] = ++tot;
	}
	
	for (int i = 0; i < n; i++)
	{
			for (int j = 0; j < n; j++)
				printf ("%d ", a[i][j]);
	printf ("\n");
	}
}
