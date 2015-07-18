#include <stdio.h>

int main ()
{
	int n;
	scanf ("%d", &n);
	if (95*n >= 300)
		printf ("%f\n", 95*n*0.85);
	else 
		printf ("%d\n", 95*n);
	return 0;
}

