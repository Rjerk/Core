#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TSIZE 45
#define FMAX  5

struct film
{
	char title[TSIZE];
	int rating; 
	struct film *next;
};

int main(void)
{
	struct film *head = NULL;
	struct film *prev, *current;
	char input[TSIZE];
	//收集并存储信息
	puts ("Enter first movie title:");
	while (gets(input) != NULL && input[0] != '\0')
	{
		current = (struct film *) malloc (sizeof (struct film));
		if (head == NULL) //第一个结构
			head = current;
		else              //后续结构
			prev->next = current;
		current->next = NULL;
		strcpy (current->title, input);
		puts ("Enter your rating <0-10>: ");
		scanf ("%d", &current->rating);
		while (getchar() != '\n')
			continue;
		puts ("Enter next movie film (empty line to stop): ");
		prev = current;
	}
	//给电影列表
	if (head == NULL)
		printf ("No data entered");
	else
		printf ("Here is the movie list: \n");
	current = head;
	while (current != NULL)
	{
		printf ("Movie %s Rating: %d \n", current->title, current->rating);
		current = current->next;
	}
	//任务已完成，因此释放所分配的内存
	current = head;
	while (current != NULL)
	{
		free (current);
		current = current->next;
	}
	printf ("Bye ~ ");
	return 0;
}
