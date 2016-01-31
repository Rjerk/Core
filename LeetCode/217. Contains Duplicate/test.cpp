#include <stdio.h>

bool containsDuplicate(int *nums, int numsSize)
{
    for (int i = 0; i < numsSize; i++)
    {
        for (int j = i + 1; j < numsSize; j++)
        {
            if (nums[i] == nums[j])
            {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    int nums[6] = {1, 2, 5, 6, 10, 2};
    if (containsDuplicate(nums, 6))
    {
         printf ("containsDuplicate\n");
    }
    else
    {
         printf ("not contains\n");
    }
    return 0;
}
