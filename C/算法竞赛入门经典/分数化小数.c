#include <stdio.h>

int main ()
{
	int a,b,c;
	while ( scanf("%d%d%d", &a, &b, &c), a!=0&&b!=0&&c!=0)
	{
		printf ("%.*lf\n", c, 1.0*a/b);
	}
}

