#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *R;
    int length;
} SSTable;

void Input(SSTable &ST)
{
    printf ("How many number you will input: ");
    scanf ("%d", &ST.length);
    ST.R = (int *) malloc (sizeof(int) * ST.length);
    printf ("Input all number: ");
    for (int i = 1; i <= ST.length; i++)
    {
        scanf ("%d", &ST.R[i]);
    }
}

int Search_bin(SSTable ST, int key)
{
    int low = 1;
    int high = ST.length;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (ST.R[mid] == key)
        {
            return mid;
        }
        else if (ST.R[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return 0;
}

int main()
{
    SSTable ST;
    Input(ST);
    int flag = Search_bin(ST, 3);
    if (flag == 0)
    {
        printf ("Not Found\n");
    }
    else
    {
        printf ("Find 3 in %d in the sequence\n", flag);
    }
}
