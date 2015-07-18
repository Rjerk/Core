#include <stdio.h>

int main()
{
	int i, j;
	for (i = 3; i <= 100; i++)
	{
		for (j = 2; j < i; j++)
			if (i % j == 0)	break;
		if (j >= i)	
			printf ("%3d", i);
	}
	printf ("\n");
}

