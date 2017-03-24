#include <stdio.h>
#include <stdlib.h>
int i, n;
struct node {
	int data;
	struct node * pre;
	struct node * next;
};

struct node *create (struct node * head){
	struct node *p1 = NULL, *p2 = NULL;
	scanf ("%d", &n);
	for (i = 1; i <= n; i++){
		p1 = (struct node *) malloc ( sizeof (struct node));
		scanf ("%d", &p1->data);
		p1 -> pre = p1 -> next = NULL;
		if ( i == n )
			head = p1;
		if ( i != 1 ){
			p2 -> next = p1;
			p1 -> pre = p2;
		}
		p2 = p1;
	}
	return head;
}

int main ()
{
	struct node * create (struct node * head);
	struct node * head = NULL, * temp;
	head = create(head);
	temp = head;
	while (temp != NULL){
		printf ("%d ", temp -> data);
		temp = temp -> pre;
	}
	return 0;
}
