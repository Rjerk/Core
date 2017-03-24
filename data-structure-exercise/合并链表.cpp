#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node * next;
} Node, *Linklist;

void CreateList(Linklist L, int num){
	Linklist p = L;
	int Data;
	while(num--){
		scanf ("%d", &Data);
		Linklist tmp = (Linklist) malloc (sizeof(Node));
		p -> next = tmp;
		p = tmp;
		p -> data = Data;
		p -> next = tmp -> next;
	}
}

Linklist MergedList(Linklist L1, Linklist L2){
	Linklist L3 = (Linklist) malloc (sizeof(Node));
	Linklist pa = L1 -> next, pb = L2 -> next, pc;
	L3 = L1;
	pc = L3;
	while (pa && pb){
		if (pa -> data <= pb -> data){
			pc -> next = pa;
			pc = pa;
			pa = pa -> next;
		}
		else{
			pc -> next = pb;
			pc = pb;
			pb = pb -> next;
		}
	}
	pc -> next = pa? pa : pb;
	free(L2);
	return L3;
}


int main ()
{
	Linklist LA = (Linklist) malloc (sizeof(Node));
	Linklist LB = (Linklist) malloc (sizeof(Node));
	Linklist LC = (Linklist) malloc (sizeof(Node));
	int n;
	printf ("Input first list: ");
	scanf ("%d", &n);
	CreateList(LA, n);
	printf ("Input second list: ");
	scanf ("%d", &n);
	CreateList(LB, n);
	LC = MergedList(LA, LB);
	LC = LC -> next;
        while (LC){
                printf ("%d ", LC -> data);
                LC = LC -> next;
        }
	printf ("\n");
	return 0;
}	
