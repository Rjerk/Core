#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int *a;
	int length;
	int heapsize;
} Sqlist;

void Input(Sqlist &L)
{
	printf ("Input the length: ");
	scanf ("%d", &L.length);
	L.a = (int *) malloc (sizeof(int) * (L.length + 1));
	printf ("Input all data: ");
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
	puts ("");
}
 
void ShellSort(Sqlist &L, int dt[], int t)
{
    for (int k = 0; k < t; k++)
    {
        int increment = dt[k];
        for (int i = increment + 1; i <= L.length; i++)
        {
            if (L.a[i] < L.a[i-increment])
            {
                L.a[0] = L.a[i];
                int j = i - increment; 
                while (j > 0 && L.a[0] < L.a[j])
				{
					L.a[j+increment] = L.a[j];
					j -= increment;
				}
                L.a[j+increment] = L.a[0];
            }
        }
    }
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

int Right(int i)
{
	return 2 * i + 1;
}

int Left(int i)
{
	return 2 * i;
}

void MaxHeapify(Sqlist &L, int i)
{
	int l = Left(i);
	int r = Right(i);
	int largest;
	if (l <= L.heapsize && L.a[l] > L.a[i])
	{
		largest = l;
	}
	else 
	{
		largest = i;
	}
	if (r <= L.heapsize && L.a[r] > L.a[largest])
	{
		largest = r;
	}
	if (largest != i)
	{
		Exchange(L.a[i], L.a[largest]);
		MaxHeapify(L, largest);
	}
}

void BuildMaxHeap(Sqlist &L)
{
	L.heapsize = L.length;
	for (int i = L.length / 2; i >= 1; i--)
	{
		MaxHeapify(L, i);
	}
}

void HeapSort(Sqlist &L)
{
	BuildMaxHeap(L);
	for (int i = L.length; i >= 2; i--)
	{
		Exchange(L.a[1], L.a[i]);
		L.heapsize--;
		MaxHeapify(L, 1);
	}
}

int main()
{
	Sqlist L;
	int dt[] = {5, 3, 1};
	puts ("ShellSort:");
	Input(L);
	ShellSort(L, dt, 3);
	Print(L);
	puts ("QuickSort:");
	Input(L);
	QuickSort(L, 1, L.length);
	Print(L);
	puts ("HeapSort:");
	Input(L);
	HeapSort(L);
	Print(L);
	return 0;
}

