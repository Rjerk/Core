#include "list.h"
#include <stdio.h>
link freelist;
void initNode (int N)
{
	int i;
	freelist = malloc ((N+1) *(sizeof *freelist));
	for (i = 0; i < N+1; i++)
		freelist[i].next = &freelist[i+1];
	freelist[N].next = NULL;
}

link newNode (int i)
{
	link x =deleteNext (freelist);
	x->item = i;
	x->next = x;
	return x;
}

void freeNode (link x)
{
	insertNext (freelist, x);
}

void insertNext (link x, link t)
{
	t->next = x->next;
	x->next = t;
}

link deleteNext (link x)
{
	link t = x->next;
	x->next = t->next;
	return x;
}

link Next (link x)
{
	return x->next;
}

int Item (link x)
{
	return x->item;
}
int main ()
{
	int i, N, M;
	scanf ("%d %d", &N, &M);
	Node t, x;
	intNodes[N];
	for (i = 2, x = newNode(1); i <= N; i++)
	{
		t = newNode[i];
		insertNext (x, t);
		x = t;
	}
	while (x != Next(x))
	{
		for (i = 1; i < M; i++)
			x = Next (x);
		freeNode (deleteNext (x));
	}
	printf ("%d\n", Item(x));
}
