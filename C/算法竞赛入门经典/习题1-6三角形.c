#include <stdio.h>

int main ()
{
	int a, b, c;
	scanf ("%d%d%d", &a, &b, &c);
	if ((a+b <= c) || (a-b >= c))
		printf ("Not a triangle\n");
	else if (a*a == b*b + c*c || b*b == a*a + c*c || c*c == a*a + b*b)
		printf ("Yes\n");
	else 
		printf ("No\n");
	return 0;
}

