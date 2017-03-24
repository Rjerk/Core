#include <stdio.h>
#include <stdlib.h>
#define  MAXSIZE  5
#define  INCREMENTSIZE 5
typedef struct {
	char *base;
	char *top;
	int stacksize;
} Stack;

int InitStack(Stack *S){//构造一个空栈S 
	S -> base = (char *) malloc (sizeof(Stack));
	if (!S -> base)
		return -1;
	S -> top = S -> base;
	S -> stacksize = MAXSIZE;
}

void StackLength1(Stack *S){//打印栈中数据元素的个数
	int length = 0;
	char *p = S -> base;
	while (p++ != S -> top)
		length++;
	printf ("%d\n", length);
}

int ReallocStacksize(Stack *S){//重新分配栈空间
	S -> base = (char *) realloc (S -> base, (S -> stacksize + INCREMENTSIZE) * sizeof(Stack));
	if (!S -> base)
		return -1;
	S -> top = S -> base + INCREMENTSIZE;
}	

void Push(Stack *S, char e){//入栈操作
	if (S -> top - S -> base == S -> stacksize)
		ReallocStacksize(S);
	*S -> top++ = e;
}

int Pop(Stack *S){//出栈操作
	char e;
	if (S -> top == S -> base)
		return -1;
	e = *--S -> top;
	printf ("%c\n", e);
}

void GetTop(Stack *S){//弹出栈顶元素
	if (S -> top != S -> base)
		printf ("%c\n",	*(S -> top - 1));
}


int main (){
	Stack *S = (Stack *) malloc (sizeof (Stack));
	InitStack(S);
	printf ("Push: a, b, c, d, e, f\nThe length:");
	Push(S, 'a');
	Push(S, 'b');
	Push(S, 'c');
	Push(S, 'd');
	Push(S, 'e');
	Push(S, 'f');
	StackLength1(S);
	printf ("The top value is ");
	GetTop(S);
	printf ("---\nPop:\n");
	for(int i = 0; i < 6; i++)
		Pop(S);
	return 0;
}
