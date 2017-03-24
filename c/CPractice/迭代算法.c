#include <stdio.h>
#include <math.h>

int main ()
{
	float a, x0, x1;
	printf ("\n Input a:");
	scanf ("%f", &a);
	if (a < 0)
		printf ("Error!\n");
	else 
	{
		x0 = a/2;
		x1 = (x0 + a/x0)/2;
		do
		{
			x0 = x1;
			x1 = (x0 + a/x0)/2;
		}while(fabs(x0-x1)>1e-5);
		printf ("sqrt(%f) = %f\n", a, x1);
	}
}

