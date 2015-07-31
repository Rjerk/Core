nclude <stdio.h>

#include <stdlib.h>



typedef struct node *link;

struct node

{

	int item;

	link next;

};



int main ()

{

	int N = 9, M = 5;

	link t = (malloc (sizeof *t));

	link x = t;

	x->item = 1;

	x->next = x;

	for (int i = 2; i <= N; i++)

	{

		x = (x->next = malloc(sizeof *x));

		x->item = i;

		x->next = t;

	}

	while (x != x->next)

	{

		for (int i = 1; i < M; i++)

			x = x->next;

		x->next = x->next->next;

		N--;

	}

	printf ("%d\n", x->item);

}
