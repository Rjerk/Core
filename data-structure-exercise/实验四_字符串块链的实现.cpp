#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  CHUNKSIZE  10
char blank = '#';
typedef struct chunk {
    char ch[CHUNKSIZE];
    struct chunk *next;
} chunk; //�����ڵ�����

typedef struct {
    chunk *head, *tail;
    int curlen;

} lstring;//��������

//��ʼ����
void InitString(lstring &T)
{
	
    T.head = T.tail = NULL;
    T.curlen = 0;
}

//���ַ������ڿ�����
void StrAssign(lstring &T, char *str)
{
    int length = T.curlen = strlen(str);
    int chunknum = length / CHUNKSIZE;
    if (length % CHUNKSIZE)
    { 
        chunknum++;
    } 
    chunk *newnode, *current;
    for (int i = 0; i < chunknum; i++)
	{
        newnode = (chunk *) malloc (sizeof(chunk));
        if (!newnode)
        { 
            exit(0);
        } 
        if (i == 0)
        { 
            T.head = current = newnode;
        } 
        else
		{
            current->next = newnode;
            current = newnode;
            current->next = NULL;
        }
        int l;
        for (l = 0; l < CHUNKSIZE && *str; l++)
		{
            *(newnode->ch + l) = *(str++);
        }
        if (!*str)
		{
            T.tail = current;
            for (; l < CHUNKSIZE; l++)
            { 
                *(current->ch + l) = blank;
            } 
        }
        puts("");
    }
}

//��T2����T1�ĵ�position���ַ�֮ǰ
void StrInsert(lstring &T1, int position, lstring &T2)
{
    T1.curlen = T1.curlen + T2.curlen;
    char *pos = T1.head->ch + position - 1;
    chunk *newnode = (chunk *) malloc (sizeof(chunk));
    *(T2.tail->ch + T2.curlen % CHUNKSIZE - 1) = ' ';
    for (int i = 0; i < CHUNKSIZE; i++)
	{
        if (i < position - 1)
        { 
            *(newnode->ch + i) = blank;
        } 
        else 
		{
            *(newnode->ch + i) = *pos;
            *(pos++) = blank;
        }
    }
    newnode->next = T1.head->next;
    T1.head->next = T2.head;
    T2.tail->next = newnode;
}

void ClearChunk(lstring &T)
{
    chunk *clear = T.head, *nextchunk = T.head;
    while (clear)
	{
        nextchunk = nextchunk->next;
        free(clear);
        clear = nextchunk;
    }
    T.head = T.tail = NULL;
    T.curlen = 0;
}

//�������е�'#'ȥ���������ַ������·��������
void Zip(lstring &T)
{
    char newstr[100];
    int j = 0;
    chunk *get_ch = T.head;
    printf ("\nZip����ǰ��T1:\n");
    while (get_ch)
	{
        for (int i = 0; i < CHUNKSIZE; i++)
		{
            if (*(get_ch->ch + i) != blank)
			{
                newstr[j] = *(get_ch->ch + i);
                j++;
            }
            printf ("%c", *(get_ch->ch + i));
        }
        get_ch = get_ch->next;
    }
    ClearChunk(T);
    StrAssign(T, newstr);
    printf ("\n����Zip�������T1:\n");
}

//��ӡ����
void StrPrint(lstring T)
{
    chunk *print_u = T.head;
    while (print_u != NULL)
	{
        for (int i = 0; i < CHUNKSIZE; i++)
        { 
            if (*(print_u->ch + i) != blank)
            { 
                printf ("%c", *(print_u->ch + i));
            }
		} 
        print_u = print_u->next;
    }
}

int main()
{
    lstring T1, T2;
    char str[100];
    printf ("�������һ�����Ȳ�����100���ַ����ַ���(������#):\n");
    InitString(T1);
    fgets(str, 100, stdin);
    StrAssign(T1, str);
    printf ("����T1Ϊ:\n");
    StrPrint(T1);
    puts("");
    printf ("������ڶ������Ȳ�����100���ַ����ַ���(������#):\n");
    InitString(T2);
    fgets(str, 100, stdin);
    StrAssign(T2, str);
    printf ("����T2Ϊ:\n");
    StrPrint(T2);
    printf ("\n������T2���뵽����T1�е�7���ַ�֮ǰ\n");
    StrInsert(T1, 7, T2);
    printf ("���в���������T1:\n");
    StrPrint(T1);
    Zip(T1);
    StrPrint(T1);
    puts("");
    return 0;
}

