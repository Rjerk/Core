/*
Description
（线性表）请写一个算法将顺序存储结构的线性表（a1...an）逆置为(an...a1)。
Input
5
1 2 3 4 5

Output
5 4 3 2 1
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node * next;
}Node, *Linklist;

Linklist head = NULL, current = NULL;

void insertByHead (int data){
	current = (Linklist) malloc ( sizeof (Node));
	current -> next = head -> next;
	current -> data = data;
	head -> next = current;
}

int main ()
{
	int num, temp;
	head = (Linklist) malloc ( sizeof (Node));
	head -> next = NULL;
	scanf ("%d", &num);
	for (; num > 0; num--){
		scanf ("%d", &temp);
		insertByHead (temp);
	}
	current = head;
	while (current -> next != NULL){
		current = current -> next;
		printf ("%d ", current -> data);
	}
	free(current);
	free(head);
	return 0;
}

