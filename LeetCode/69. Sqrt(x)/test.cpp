#include <stdio.h>

int mySqrt(int x)
{
    int low = 0, high = x, ans;
    if (x < 2)
    {
        return x;
    }
    while (low < high - 1)
    {
        ans = low + (high - low) / 2;
	printf ("low = %d, high = %d, ans = %d\n", low, high, ans);
        if (ans <= x / ans)
        {
            low = ans;
        }
        else
        {
            high = ans;
        }
    }
    return low;
}
int main()
{
    printf ("sqrt(1024) = %d", mySqrt(1024));
    return 0;
}
