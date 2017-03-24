#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char item[20];
    struct node *next;
} StackNode, *Stack; //������ʽ��ջ�ڵ����ͺͶ�ջ����

typedef struct queuenode {
    char item[20];
    struct queuenode *next;
} QueueNode; //������ʽ���нڵ�����

typedef struct {
    queuenode *front; //����ͷָ��
    queuenode *rear; //����βָ��
} Queue; //������ʽ��������

//����һ����ջ, SΪջ��ָ��
void CreateStack(Stack &S)
{
    S = NULL;
}

//�ж�ջ��
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

//����һ�������Ķ�ջ�ڵ㣬�������ڸ���data��ָ����
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

//��data��ָ������ջ
void Push(Stack &S, char *data)
{
    StackNode *innode = CreateStackNode(data);
    innode -> next = S;
    S = innode;
}

//��ջ�����ڵ����ݴ���data
void Pop(Stack &S, char *data){
    StackNode *outnode = S;
    if (!StackEmpty(S))
	{
        S = outnode -> next;
        strcpy(data, outnode -> item);
        free(outnode);
    }
}

//�������´�ӡջ��Ԫ��
void PrintStack(Stack S)
{
    StackNode *printit = S;
    if (!StackEmpty(S))
	{
        printf ("\nջ��Ԫ��: ");
        while (printit)
		{
            printf ("%s, ", printit -> item);
            printit = printit -> next;
        }
    }
}

//�����ն���, Q��������ͷβָ��
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

//������ʽ���нڵ�, �������и�����data��ָ����
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

//���
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

//���ӣ������ڵ������ݸ��Ƹ�data
void OutQueue(Queue &Q, char *data){
    QueueNode *outnode;
    if (QueueEmpty(Q))
    { 
        printf ("\n�ӿգ����Ӵ���\n");
    } 
    else
	{
        outnode = Q.front;
        strcpy(data, Q.front -> item);
        Q.front = outnode -> next;
        free(outnode);
    }
}

//��ͷ��β��ӡ����Ԫ��
void PrintQueue(Queue Q)
{
    QueueNode *printit = Q.front;
    if (!QueueEmpty(Q))
	{
        printf ("\n����Ԫ��: ");
        while (printit)
		{
            printf ("%s, ", printit -> item);
            printit = printit -> next;
        }
    }
}

//������������ȼ�
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

//С����ƥ�� 
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


//���������׺���ʽת��Ϊ��׺���ʽ
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
        	//��������������뻺���������ֱ�����
            isnum = 1;
            temp[j++] = expression[i++];
        }
        if (isnum)
		{ //������� 
            temp[j] = '\0';
            InQueue(Queue_opr, temp);
        }
        else
		{ //��������Ĳ���
            temp[0] = expression[i++];
            temp[1] = '\0';
            switch(temp[0])
			{
                case '(': //��Ϊ'('��ֱ��ѹ��ջ
                    Push(Stack_opr, temp);
                    break;
                case '+':
                case '-':
                case '*':
                case '/':
                    if (!StackEmpty(Stack_opr))
					{ 
                    	//��ջ�ǿգ������е����������������ȼ��ߵĳ�ջ���
                        //���������������ȼ��͵�ѹ��ջ��
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
					{ //�������ڵķ������������
                        Pop(Stack_opr, opr);
                        InQueue(Queue_opr, opr);
                    }
                    Pop(Stack_opr, opr); //Ȼ��'('����
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

//�����׺���ʽ
void Calculate(Queue &Q)
{
    char temp[100]; //�����ȡ�ĺ�׺���ʽ�Ļ�����
	char num[10]; //��Ų���������
    double fa, fb;
    Stack Stack_opr;
    CreateStack(Stack_opr);
    while (!QueueEmpty(Q))
	{
        OutQueue(Q, temp); //���Ӻ�����temp�еȴ�����
        if (temp[0] >= '0' && temp[0] <= '9') //������������ջ
        {
		    Push(Stack_opr, temp);
		} 
        else
		{//����������������ֳ�ջ���ֱ�ת��Ϊ��������ֵfa��fb������
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
                        printf ("\n��0����");
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
    printf ("\n��������%s", num);
}

int main()
{
    char expression[200];
    Queue Queue_opr;
    CreateQueue(Queue_opr);
    printf ("\n��������׺���ʽ:\n");
    fgets(expression, 200, stdin);
    printf ("%s", expression);
    if (!ParenthesisMatch(expression))
	{
    	printf ("С���Ų�ƥ�䣡\n");
    	exit(0);
	}
    Transform(Queue_opr, expression);
    Calculate(Queue_opr);
    puts("");
    return 0;
}

