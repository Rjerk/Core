#include <stdio.h>
#include <stdlib.h>

bool isHappy(int n)
{
    while (1)
    {
        int sum = 0;
        while (n != 0)
        {
            sum += (n % 10) * (n % 10);
            n /= 10;
        }
        n = sum;
        printf ("n = %d\n", n);
        if (n == 4)
        {
            return false;
        }
        if (n == 1)
        {
            return true;
        }
    }
}

int main()
{
    if(isHappy(19))
        printf ("This is a happy number\n");
    else
        printf ("This is not a happy number\n");
    return 0;
}
