#include <stdio.h>

int main ()
{
	int n;
	scanf ("%d", &n);
	while (n--)
	{
		int a[9];
		for (int i = 0; i < 9; i++)
			scanf ("%d", &a[i]);
		for (int k = 0; k < 3; k++)
		{
			for (int j = k; j < 9; j += 3)
			{
				printf ("%d ", a[j]);
			}
			printf ("\n");	
		}	
	}	
	return 0;
}

