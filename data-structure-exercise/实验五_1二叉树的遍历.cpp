#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  STACKSIZE  10
#define  INCREMENT  10

typedef struct tree{
    char data;
    struct tree *lchild;
    struct tree *rchild;
} Bitnode, *Bitree;

typedef struct {
    Bitree *top;
    Bitree *base;
    int stacksize;
} Stack;

//Initilize stack
void InitStack(Stack &S)
{
    S.base = (Bitree *) malloc (sizeof(Bitree) * STACKSIZE);
    if (!S.base)
	{
        printf ("Stack malloc wrongs\n");
        exit(0);
    }
    S.top = S.base;
    S.stacksize = STACKSIZE;
}

//Push stack
void Push(Stack &S, Bitree e
){
    if (S.top - S.base >= S.stacksize)
	{
        S.base = (Bitree *) realloc (S.base, (S.stacksize + INCREMENT) * sizeof(Bitree));
        if (!S.base)
		{
            printf ("Stack realloc wrongs\n");
            exit(1);
        }
        S.top = S.base + S.stacksize;
        S.stacksize += INCREMENT;
    }
    *(S.top++) = e;
}

//Pop Stack
Bitree Pop(Stack &S)
{
    if (S.top == S.base)
	{
        printf ("Stack is empty\n");
        exit(0);
    }
    return *(--S.top);
}

//Stack is empty or not
bool StackEmpty(Stack S){
    if (S.top == S.base)
    { 
        return true;
    } 
    return false;
}

//Get top element
Bitnode* StackTop(Stack S)
{
    return *(S.top-1);
}

//Create binary tree
void CreateBitree(Bitree &T)
{
    char  ch;
    scanf ("%c", &ch);
    if (ch == '#')
    { 
        T = NULL;
    }
	else
	{
        T = (Bitnode *) malloc (sizeof(Bitnode));
        if (!T)
		{
            printf ("Tree malloc wrongs\n");
            exit(0);
        }
        T -> data = ch;
        CreateBitree(T -> lchild);
        CreateBitree(T -> rchild);
    }
}

//Pre-order traverse the tree recursively
void PreOrderBitree1(Bitree T)
{
    if (T){
        printf ("%c ", T -> data);
        PreOrderBitree1(T -> lchild);
        PreOrderBitree1(T -> rchild);
    }
}

//Pre-order traverse the tree non-recursively
void PreOrderBitree2(Bitree T)
{
    Bitree current = T;
    Stack S;
    InitStack(S);
    while (current || !StackEmpty(S)){
        if (current){
            printf ("%c ", current -> data);
            Push(S, current);
            current = current -> lchild;
        }
        else {
            current = Pop(S);
            current = current -> rchild;
        }
    }
}

//In-order traverse the tree recursively
void InOrderBitree1(Bitree T)
{
    if (T)
	{
        InOrderBitree1(T -> lchild);
        printf ("%c ", T -> data);
        InOrderBitree1(T -> rchild);
    }
}

//In-order traverse the tree non-recursively
void InOrderBitree2(Bitree T)
{
    Stack S;
    InitStack(S);
    Bitree current = T;
    while (current || !StackEmpty(S))
	{
        if (current)
		{
            Push(S, current);
            current = current -> lchild;
        }
        else
		{
            current = Pop(S);
            printf ("%c ", current -> data);
            current = current -> rchild;
        }
    }
}

//Post-Order traverse the tree non-recursively
void PosOrderBitree1(Bitree T
){
    if (T != NULL){
        PosOrderBitree1(T -> lchild);
        PosOrderBitree1(T -> rchild);
        printf ("%c ", T -> data);
    }
}

//Post-Order traverse the tree non-recursively
void PosOrderBitree2(Bitree T)
{
    Stack S;
    InitStack(S);
    Bitree current = T;
    Bitree visited = NULL;
    while (current || !StackEmpty(S))
	{
        while (current)
		{
            Push(S, current);
            current = current -> lchild;
        }
        current = StackTop(S);
        if (!current -> rchild || current -> rchild == visited)
		{
            printf ("%c ", current -> data);
            visited = current;
            Bitree rubbish = Pop(S);
            current = NULL;
        }
        else
        {
            current = current -> rchild;
    	}
    }
}

//Obtain node's number in tree whose degree is 0/1/2
int GetNumDegree0(Bitree T)
{
    if (!T)
    {
        return 0;
    }
    else if (!T -> lchild && !T -> rchild)
    {
        return 1;
	}
	else
	{
        return GetNumDegree0(T -> lchild) + GetNumDegree0(T -> rchild);
    }

}

int GetNumDegree1(Bitree T)
{
    if (!T)
    {
        return 0;
    }
    else if (!T -> lchild ^ !T -> rchild)
    {
        return 1 + GetNumDegree1(T -> lchild) + GetNumDegree1(T -> rchild);
    }
    else
    {
        return GetNumDegree1(T -> lchild) + GetNumDegree1(T -> rchild);
    }
}

int GetNumDegree2(Bitree T)
{
    if (!T)
    {
        return 0;
    }
    else if (T -> lchild && T -> rchild)
    {
        return 1 + GetNumDegree2(T -> lchild) + GetNumDegree2(T -> rchild);
    }
    else
    {
        return GetNumDegree2(T -> lchild) + GetNumDegree2(T -> rchild);
    }
}

//Depth of the tree
int BitreeDepth(Bitree T)
{
    if (T != NULL)
	{
        int depthleft = BitreeDepth(T -> lchild);
        int depthright = BitreeDepth(T -> rchild);
        return (depthleft + depthright ? depthleft : depthright) + 1;
    }
    return 0;
}

int main ()
{
    Bitree T;
    printf ("\n输入二叉树:\n");
    CreateBitree(T);
    printf ("\n先序打印二叉树(递归):\n");
    PreOrderBitree1(T);
    printf ("\n先序打印二叉树(非递归):\n");
    PreOrderBitree2(T);
    printf ("\n中序打印二叉树(递归):\n");
    InOrderBitree1(T);
    printf ("\n中序打印二叉树(非递归):\n");
    InOrderBitree2(T);
    printf ("\n后序打印二叉树(递归):\n");
    PosOrderBitree1(T);
    printf ("\n后序打印二叉树(非递归):\n");
    PosOrderBitree2(T);
    puts("");
    printf ("\n度为0的节点个数： %d\n", GetNumDegree0(T));
    printf ("\n度为1的节点个数： %d\n", GetNumDegree1(T));
    printf ("\n度为2的节点个数： %d\n", GetNumDegree2(T));
    printf ("\n树的深度为: %d\n", BitreeDepth(T));
    puts("");
	return 0;
}


