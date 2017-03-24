#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char item[20];
    struct node *next;
} StackNode, *Stack; //定义链式堆栈节点类型和堆栈类型

typedef struct queuenode {
    char item[20];
    struct queuenode *next;
} QueueNode; //定义链式队列节点类型

typedef struct {
    queuenode *front; //定义头指针
    queuenode *rear; //定义尾指针
} Queue; //定义链式队列类型

//穿件一个空栈, S为栈顶指针
void CreateStack(Stack &S)
{
    S = NULL;
}

//判断栈空
int StackEmpty(Stack S)
{
    if (!S)
    { 
        return 1;
    } 
    else
    {
	    return 0;
	} 
}

//创建一个单独的堆栈节点，并向其内复制data所指数据
StackNode *CreateStackNode(char *data)
{
    StackNode *newnode = (StackNode *) malloc (sizeof(StackNode));
    if (!newnode)
    { 
        exit(0);
    } 
    else
	{
        strcpy(newnode -> item, data);
        newnode -> next = NULL;
    }
    return newnode;
}

//将data所指数据入栈
void Push(Stack &S, char *data)
{
    StackNode *innode = CreateStackNode(data);
    innode -> next = S;
    S = innode;
}

//出栈并将节点数据传入data
void Pop(Stack &S, char *data){
    StackNode *outnode = S;
    if (!StackEmpty(S))
	{
        S = outnode -> next;
        strcpy(data, outnode -> item);
        free(outnode);
    }
}

//至顶而下打印栈内元素
void PrintStack(Stack S)
{
    StackNode *printit = S;
    if (!StackEmpty(S))
	{
        printf ("\n栈内元素: ");
        while (printit)
		{
            printf ("%s, ", printit -> item);
            printit = printit -> next;
        }
    }
}

//创建空队列, Q包含队列头尾指针
void CreateQueue(Queue &Q)
{
    Q.front = Q.rear = NULL;
}

int QueueEmpty(Queue Q)
{
    if (Q.front == NULL)
    { 
        return 1;
    } 
    else
    {
	    return 0;
	}
} 

//创建链式队列节点, 并向其中复制入data所指数据
QueueNode *CreateQueueNode(char *data)
{
    QueueNode *innode = (QueueNode *) malloc (sizeof(QueueNode));
    if (innode == NULL)
    {
	    exit(0);
    }
	else
	{
        strcpy(innode -> item, data);
        innode -> next = NULL;
    }
    return innode;
}

//入队
void InQueue(Queue &Q, char *data)
{
    QueueNode *innode = CreateQueueNode(data);
    if (QueueEmpty(Q))
    { 
        Q.front = Q.rear = innode;
    } 
    else
	{
        Q.rear -> next = innode;
        Q.rear = innode;
    }
}

//出队，并将节点内数据复制给data
void OutQueue(Queue &Q, char *data){
    QueueNode *outnode;
    if (QueueEmpty(Q))
    { 
        printf ("\n队空，出队错误\n");
    } 
    else
	{
        outnode = Q.front;
        strcpy(data, Q.front -> item);
        Q.front = outnode -> next;
        free(outnode);
    }
}

//从头至尾打印队列元素
void PrintQueue(Queue Q)
{
    QueueNode *printit = Q.front;
    if (!QueueEmpty(Q))
	{
        printf ("\n队内元素: ");
        while (printit)
		{
            printf ("%s, ", printit -> item);
            printit = printit -> next;
        }
    }
}

//设置运算符优先级
int Priority(char opr)
{
    switch(opr){
    	
        case '(': return 0;
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
    }
}

//小括号匹配 
int ParenthesisMatch(char expression[])
{
	char temp[10];
	Stack Stack_opr;
	CreateStack(Stack_opr);
	for (int i = 0; expression[i] != '\0'; i++)
	{
		if (expression[i] == '(')
		{
			temp[0] = expression[i];
			temp[1] = '\0';
			Push(Stack_opr, temp);
		}
		else if (expression[i] == ')')
		{
			if (!StackEmpty(Stack_opr))
			{ 
				Pop(Stack_opr, temp);
			} 
			else
			{ 
				return 0;
			} 
		}
	}
	if (StackEmpty(Stack_opr))
	{ 
		return 1;
	} 
	else
	{ 
		return 0;
	} 
}


//将输入的中缀表达式转化为后缀表达式
void Transform(Queue &Queue_opr, char expression[])
{
    char temp[20], opr[20];
    int i = 0, j, isnum;
    Stack Stack_opr;
    CreateStack(Stack_opr);
    while (expression[i] != '\0')
	{
        j = isnum = 0;
        while (expression[i] >= '0' && expression[i] <= '9')
		{
        	//若是数字则将其放入缓存区并随后直接入队
            isnum = 1;
            temp[j++] = expression[i++];
        }
        if (isnum)
		{ //数字入队 
            temp[j] = '\0';
            InQueue(Queue_opr, temp);
        }
        else
		{ //对运算符的操作
            temp[0] = expression[i++];
            temp[1] = '\0';
            switch(temp[0])
			{
                case '(': //若为'('则直接压入栈
                    Push(Stack_opr, temp);
                    break;
                case '+':
                case '-':
                case '*':
                case '/':
                    if (!StackEmpty(Stack_opr))
					{ 
                    	//若栈非空，则将其中的运算符则将运算符优先级高的出栈入队
                        //将缓存区符号优先级低的压入栈中
                        while (Priority(temp[0])<= Priority(Stack_opr -> item[0]))
						{
                            Pop(Stack_opr, opr);
                            InQueue(Queue_opr, opr);
                            if (StackEmpty(Stack_opr))
                                break;
                        }
                    } 
                    Push(Stack_opr, temp);
                    break;
                case ')':
                    while (Stack_opr -> item[0] != '(')
					{ //将括号内的符号移入队列中
                        Pop(Stack_opr, opr);
                        InQueue(Queue_opr, opr);
                    }
                    Pop(Stack_opr, opr); //然后将'('弹出
                    break;
            }
        }
        PrintStack(Stack_opr);
        PrintQueue(Queue_opr);
    }
    while (!StackEmpty(Stack_opr))
	{
    	Pop(Stack_opr, opr);
    	InQueue(Queue_opr, opr);
	}
	PrintQueue(Queue_opr);
}

//计算后缀表达式
void Calculate(Queue &Q)
{
    char temp[100]; //存放提取的后缀表达式的缓存区
	char num[10]; //存放操作的整数
    double fa, fb;
    Stack Stack_opr;
    CreateStack(Stack_opr);
    while (!QueueEmpty(Q))
	{
        OutQueue(Q, temp); //出队后存放在temp中等待操作
        if (temp[0] >= '0' && temp[0] <= '9') //若是数字则入栈
        {
		    Push(Stack_opr, temp);
		} 
        else
		{//遇到运算符则将两数字出栈并分别转化为浮点数赋值fa和fb并计算
            Pop(Stack_opr, num);
            fa = atof(num);
            //atof(), the function of stdlib will convert a string to a double,
            //The atof function skips all white-space characters at the beginning of the string,
            //converts the subsequent characters as part of the number,
            //and then stops when it encounters the first character that isn't a number
            Pop(Stack_opr, num);
            fb = atof(num);
            switch(temp[0])
			{
                case '+': fb += fa; break;
                case '-': fb -= fa; break;
                case '*': fb *= fa; break;
                case '/':
                    if (fa == 0)
					{
                        printf ("\n除0错误！");
                        exit(0);
                    }
                    else
					{
                        fb /= fa;
                        break;
                    }
            }
            sprintf (num, "%f", fb);
            //The C library function int sprintf(char *str, const char *format, ...)
            //sends formatted output to a string pointed to, by str.
            Push(Stack_opr, num);
        }
    }
    Pop(Stack_opr, num);
    printf ("\n运算结果：%s", num);
}

int main()
{
    char expression[200];
    Queue Queue_opr;
    CreateQueue(Queue_opr);
    printf ("\n请输入中缀表达式:\n");
    fgets(expression, 200, stdin);
    printf ("%s", expression);
    if (!ParenthesisMatch(expression))
	{
    	printf ("小括号不匹配！\n");
    	exit(0);
	}
    Transform(Queue_opr, expression);
    Calculate(Queue_opr);
    puts("");
    return 0;
}

