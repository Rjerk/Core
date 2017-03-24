#include <stdio.h>

int main ()
{
	int a;
	scanf ("%d", &a);
	int m;
	int b = a / 10;
	switch (b)
	{
		case 1 : 
		case 2 : printf ("m = 1\n");break;
		case 3 : printf ("m = 2\n");break;
		case 4 : printf ("m = 3\n");break;
		case 5 : printf ("m = 4\n");break;
		default: printf ("m = 5\n");
	}
}
