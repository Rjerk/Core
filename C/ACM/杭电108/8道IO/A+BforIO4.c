#include <stdio.h>
 
int main ()
{
        int sum = 0, a, n, i;scanf ("%d", &n);
        while (n != 0)
        {
                for (i = 0; i < n; i++)
                {
                        scanf ("%d", &a);
                        sum += a;
                }
                printf ("%d\n", sum);
                sum = 0;
                scanf ("%d", &n);
        }
        return 0;
}

