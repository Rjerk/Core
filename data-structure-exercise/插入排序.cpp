#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *a;
    int length;
} Sqlist;

void Input(Sqlist &L)
{
    printf ("Input length: ");
    scanf ("%d", &L.length);
    L.a = (int *) malloc (sizeof(int) * (L.length + 1));
    printf ("Input all data: ");
    for (int i = 1; i <= L.length; i++)
    {
        scanf ("%d", &L.a[i]);
    }
}

void InsertSort(Sqlist &L)
{
    for (int j = 2; j <= L.length; j++)
    {
        int key = L.a[j];
        int i = j - 1;
        while (i > 0 && L.a[i] > key){
            L.a[i+1] = L.a[i];
            i--;
        }
        L.a[i+1] = key;
    }
}

void Print(Sqlist L)
{
    printf ("After InsertSort: ");
    for (int i = 1; i <= L.length; i++)
    {
        printf ("%d ", L.a[i]);
    }
    free(L.a);
    puts("");
}

int main()
{
    Sqlist L;
    Input(L);
    InsertSort(L);
    Print(L);
    return 0;
}
