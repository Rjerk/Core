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

int Search_seq(SSTable ST, int key)
{
    ST.R[0] = key;
    int i;
    for (i = ST.length; ST.R[i] != key; i--);
    return i;
}

int main()
{
    SSTable ST;
    Input(ST);
    int flag = Search_seq(ST, 3);
    if (flag == 0)
    {
        printf ("Not Found\n");
    }
    else
    {
        printf ("Find 3 in %d in the sequence\n", flag);
    }
}
