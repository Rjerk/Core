#include <stdio.h>
#include <stdlib.h>
#define  LIST_INIT_SIZE 10 //���Ա�洢�ռ�ĳ�ʼ������
#define  LIST_INCREMENT 10 //���Ա�洢�ռ�ķ�������
#define  OK 1	
#define  OVERFLOW -1	
#define  ERROR 0
typedef  int Status; //Status�Ǻ��������ͣ���ֵ�Ǻ������״̬����
typedef struct {
	int *elem; //�洢�ռ�Ļ���ַ
	int length; //���Ա�ĳ���
	int listsize; //��ǰ����Ĵ洢����
} List;

Status InitList(List &L)
{//����һ���յ����Ա�L
    L.elem = (int *) malloc (sizeof(int) * LIST_INIT_SIZE); //�洢����ռ�
    if (L.elem == NULL)
    { 
        exit(OVERFLOW); //�洢����ʧ���˳�
    } 
    L.length = 0; //�ձ���Ϊ0
    L.listsize = LIST_INIT_SIZE; //��ʼ�洢����
    return OK;
}

Status ClearList(List &L)
{ //��L����Ϊ�ձ�
	L.length = 0; //����Ϊ0
	return OK;
}

Status ListEmpty(List L)
{ //���L�Ƿ�Ϊ�ձ�
	if (L.length == 0)
	{
		return OK; //��Ϊ0��Ϊ�ձ�
	} 
	else 
	{ 
		return ERROR;
	}
} 

int ListLength(List L)
{ //����L������Ԫ�ظ���
	return L.length;
}

int GetValue(List L, int i, int &e)
{ //��e����L�е�i������Ԫ�ص�ֵ
	if (i < 1 || i > L.length)
	{
		return ERROR; //i���Ϸ�
	} 
	e = L.elem[i-1];
	return e;
}

Status InputValue(List &L)
{//�����Ա����������Ԫ��
	int value;
	for (int i = 0; i < 10; i++)
	{//����10������Ԫ��
		scanf ("%d", &value);
		L.elem[i] = value; 
		L.length++; //ÿ����һ��Ԫ�ر���1
	}
	return OK;
}

Status SortValue(List &L)
{//��ð�����򷨸����Ա�������Ԫ������
	int temp;
	for (int i = 0; i < L.length - 1; i++)
	{ 
		for (int j = 0; j < L.length - 1; j++)
		{ 
			if (L.elem[j] > L.elem[j+1])
			{
				temp = L.elem[j];
				L.elem[j] = L.elem[j+1];
				L.elem[j+1] = temp;
			}
		} 
	} 
	return OK;
}

Status ListRealloc(List &L)
{//�����Ա�洢�ռ����ӷ���
    int *newbase = (int *) realloc (L.elem,
    			(L.listsize + LIST_INCREMENT) * sizeof (int));
    if (newbase == NULL)
	{ 
        exit(OVERFLOW);//���ӷ���ʧ���˳�
    } 
    L.elem = newbase; //�»�ַ
    L.listsize += LIST_INCREMENT; //���Ӵ洢����
    return OK;
}


Status InsertValue(List &L, int i, int e)
{//�ڵ�i��λ�ò����µ�Ԫ��e������1
	if (i < 1 || i > L.length + 1)
	{
		return ERROR; //iֵ���Ϸ�
	} 
	if (L.length >= L.listsize)
	{ 
		ListRealloc(L); //���洢�ռ䲻�������·���
	} 
	int *q = &(L.elem[i-1]); //��ǵ�i��λ��
	for (int *p = &(L.elem[L.length-1]); p >= q; p--)
	{ 
		*(p+1) = *p; //����i��λ�õ�Ԫ��ȫ������һλ
	} 
	*q = e; //����e
	L.length++; //����1
	return OK;
}

Status MergeList(List La, List Lb, List &Lc)
{//�ϲ��������Ա�
	Lc.length = La.length + Lb.length; 
	Lc.elem = (int *) malloc (sizeof(int) * Lc.length); //Ϊ���ϲ��ı����洢�ռ�
	Lc.listsize = La.listsize + Lb.listsize; //��ʼ����
	if (Lc.elem == NULL)
	{ 
		exit(OVERFLOW); //����ʧ���˳�
	} 
	for (int i = 0; i < Lc.length; i++)
	{ 
		Lc.elem[i] = La.elem[i]; //��LaԪ�ط���ǰ��
	} 
	for (int j = 0; j < Lb.length; j++)
	{ 
		Lc.elem[j+La.length] = Lb.elem[j]; //��LbԪ�ط��ں���
	} 
	return OK;
}

int DeleteValue(List &L, int i, int &e)
{//ɾ��L�ĵ�i������Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1
	e = L.elem[i-1]; //����ɾ����Ԫ��
	int *q = &(L.elem[i]);//��ǵ�i��Ԫ�ص�λ��
	for (; q < &(L.elem[L.length-1]); q++)
	{ 
		*q = *(q+1); //����i��λ�ú��Ԫ��ȫ����ǰ�ƶ�һλ
	}
	L.length--; //����1
	return e;
}
	
Status ListPrint(List L)
{//��ӡ���Ա������Ԫ��
	for (int i = 0; i < L.length; i++)
	{
		printf ("%d ", L.elem[i]);
	} 
	printf ("\n");
	return OK;
}

int main()
{
	List L1;
	InitList(L1);
	printf ("Ϊ���Ա�L1����10�����֣�\n");
	InputValue(L1);
	printf ("L1�е�����Ԫ��Ϊ��\n");
	ListPrint(L1);
	printf ("����L1:\n");
	SortValue(L1);
	ListPrint(L1);
	printf ("��L1�����λ�ò����µ�����Ԫ��100��\n");
	InsertValue(L1, 5, 100);
	ListPrint(L1);
	printf ("�ٴ�����L1��\n");
	SortValue(L1);
	ListPrint(L1);
	List L2, L3;
	InitList(L2);
	printf ("\nΪ���Ա�L2����10�����֣�\n");
	InputValue(L2);
	printf ("L2�е�����Ԫ��Ϊ��\n");
	ListPrint(L2);
	InitList(L3);
	printf ("\n��L1��L2�ϲ���L3�У��ϲ����L3�е�����Ԫ��Ϊ��\n");
	MergeList(L1, L2, L3);
	ListPrint(L3);
	printf ("L3�ĳ���Ϊ��%d\n", ListLength(L3));
	printf ("����L3:\n");
	SortValue(L3);
	ListPrint(L3);
	ClearList(L2);
	printf ("����L2Ϊ�ձ�, �����...");
	if (ListEmpty(L2))
	{
		printf ("���óɹ�\n");
	} 
	else
	{ 
		printf ("����ʧ��\n");
	} 
	printf ("���L3��15������Ԫ��...");
	int e;
	printf ("L3��15������Ԫ��Ϊ:%d\n", GetValue(L3, 15, e));
	printf ("����ɾ����15��Ԫ��%d...", DeleteValue(L3, 15, e));
	printf ("ɾ����ϣ����L3�д�ʱ������Ԫ��Ϊ:\n");
	ListPrint(L3);
	printf ("��ʱL3�ĳ���Ϊ:%d\n", ListLength(L3));
	printf ("\nʵ����ϣ�������������! :) \n");
	return 0;
}

