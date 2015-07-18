#include <stdio.h>

int main ()
{
	int num;
	int a, b, c;
	int n = 1;
	while ( (scanf ("%d%d%d", &a, &b, &c)) == 3 )
	{
		for ( num = 11; num <= 100; num++)
		{
			if ( num % 3 == a && num % 5 == b && num % 7 == c)
			{	
				printf ("case %d : %d \n", n, num);
				break;
			}
		}
		if ( num > 100)
			printf ("case %d : No answer\n", n);
		n++;
	}
}
