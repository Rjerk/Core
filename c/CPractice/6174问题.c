#include <stdio.h>
int main ()
{
	int n, b, k=0;
	scanf ("%d", &n);
	while (n--)
	{
		int a[4];
		scanf ("%d", &b);
		printf ("Come");
		a[0] = b / 1000;
                a[1] = b / 100 % 10;
                a[2] = b / 10 % 10;
                a[3] = b % 10;
		printf ("%d  %d", b, a[1]);
		for (; b != 6174; )
		{
			for (int i=0; i < 3; i++)
			{
				for (int j=i+1; j < 4; j++)
				{
					int temp;
					if (a[i] < a[j])
					{
						temp = a[i];
						a[i] = a[j];
						a[j] = temp;
					}
				}
			}
			int m, max, min;
			for (int i=0; i < 4;i++)
			{
				max = 10 * max + a[i];
				min = 10 * min + a[i-1];
			}
			m = max - min;
			a[1] = m / 1000;
			a[2] = m / 100 % 10;
			a[3] = m / 10 % 10;
			a[4] = m % 10;
			k++;
		}	
		printf ("%d\n", k);
	}
}

