#include <stdio.h>

int main ()
{
	int b;
	while (scanf ("%d", &b) != EOF)
	{
		int s=0;
		for (int i=0; i <= b; i++)
		{
			if (i%2 == 0)
				s += i;
		}
		printf ("%d\n", s);
	}
}

