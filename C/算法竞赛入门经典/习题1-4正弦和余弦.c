#include <stdio.h>
#include <math.h>

int main ()
{
	int n;
	scanf ("%d", &n);
	printf ("%f %f\n", sin( n*acos(-1)/360), cos(n*acos(-1)/360));
	return 0;
}

