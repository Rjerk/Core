#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *a;
    int length;
} Sqlist;

void Input(Sqlist &L)
{
    printf ("Input the length: ");
    scanf ("%d", &L.length);
    L.a = (int *) malloc (sizeof(int) * (L.length+1));
    printf ("Input the data: ");
    for (int i = 1; i <= L.length; i++)
    {
        scanf ("%d", &L.a[i]);
    }
}

void Print(Sqlist L)
{
    printf ("After Sort: ");
    for (int i = 1; i <= L.length; i++)
    {
        printf ("%d ", L.a[i]);
    }
    free(L.a);
    puts("");
}

void Exchange(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int Partition(Sqlist &L, int &p, int &r)
{
    int x = L.a[r];
    int i = p - 1;
    for (int j = p; j <= r - 1; j++)
    {
        if (L.a[j] <= x)
        {
            i++;
            Exchange(L.a[i], L.a[j]);
        }
    }
    Exchange(L.a[i+1], L.a[r]);
    return i + 1;
}

void QuickSort(Sqlist &L, int p, int r)
{
    if (p < r)
    {
        int q = Partition(L, p, r);
        QuickSort(L, p, q-1);
        QuickSort(L, q+1, r);
    }
}

int main()
{
    Sqlist L;
    Input(L);
    QuickSort(L, 1, L.length);
    Print(L);
    return 0;
}
