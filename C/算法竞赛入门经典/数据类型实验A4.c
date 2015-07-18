#include <stdio.h>

int main ()
{
	printf ("%f\n", 1.0/0.0);
	printf ("%f\n", 0.0/0.0);
	printf ("%f\n", 1.0/(1.0/0.0));
	return 0;
}
	
