#include <stdio.h>
#include <stdlib.h>
#define  LIST_INIT_SIZE 10 //线性表存储空间的初始分配量
#define  LIST_INCREMENT 10 //线性表存储空间的分配增量
#define  OK 1	
#define  OVERFLOW -1	
#define  ERROR 0
typedef  int Status; //Status是函数的类型，其值是函数结果状态代码
typedef struct {
	int *elem; //存储空间的基地址
	int length; //线性表的长度
	int listsize; //当前分配的存储容量
} List;

Status InitList(List &L)
{//构造一个空的线性表L
    L.elem = (int *) malloc (sizeof(int) * LIST_INIT_SIZE); //存储分配空间
    if (L.elem == NULL)
    { 
        exit(OVERFLOW); //存储分配失败退出
    } 
    L.length = 0; //空表长度为0
    L.listsize = LIST_INIT_SIZE; //初始存储容量
    return OK;
}

Status ClearList(List &L)
{ //将L重置为空表
	L.length = 0; //表长置为0
	return OK;
}

Status ListEmpty(List L)
{ //检测L是否为空表
	if (L.length == 0)
	{
		return OK; //表长为0则为空表
	} 
	else 
	{ 
		return ERROR;
	}
} 

int ListLength(List L)
{ //返回L中数据元素个数
	return L.length;
}

int GetValue(List L, int i, int &e)
{ //用e返回L中第i个数据元素的值
	if (i < 1 || i > L.length)
	{
		return ERROR; //i不合法
	} 
	e = L.elem[i-1];
	return e;
}

Status InputValue(List &L)
{//向线性表中添加数据元素
	int value;
	for (int i = 0; i < 10; i++)
	{//输入10个数据元素
		scanf ("%d", &value);
		L.elem[i] = value; 
		L.length++; //每输入一个元素表长加1
	}
	return OK;
}

Status SortValue(List &L)
{//用冒泡排序法给线性表中数据元素排序
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
{//给线性表存储空间增加分配
    int *newbase = (int *) realloc (L.elem,
    			(L.listsize + LIST_INCREMENT) * sizeof (int));
    if (newbase == NULL)
	{ 
        exit(OVERFLOW);//增加分配失败退出
    } 
    L.elem = newbase; //新基址
    L.listsize += LIST_INCREMENT; //增加存储容量
    return OK;
}


Status InsertValue(List &L, int i, int e)
{//在第i个位置插入新的元素e，表长加1
	if (i < 1 || i > L.length + 1)
	{
		return ERROR; //i值不合法
	} 
	if (L.length >= L.listsize)
	{ 
		ListRealloc(L); //若存储空间不够则重新分配
	} 
	int *q = &(L.elem[i-1]); //标记第i个位置
	for (int *p = &(L.elem[L.length-1]); p >= q; p--)
	{ 
		*(p+1) = *p; //将第i个位置的元素全部后移一位
	} 
	*q = e; //插入e
	L.length++; //表长加1
	return OK;
}

Status MergeList(List La, List Lb, List &Lc)
{//合并两个线性表
	Lc.length = La.length + Lb.length; 
	Lc.elem = (int *) malloc (sizeof(int) * Lc.length); //为将合并的表分配存储空间
	Lc.listsize = La.listsize + Lb.listsize; //初始容量
	if (Lc.elem == NULL)
	{ 
		exit(OVERFLOW); //分配失败退出
	} 
	for (int i = 0; i < Lc.length; i++)
	{ 
		Lc.elem[i] = La.elem[i]; //将La元素放在前面
	} 
	for (int j = 0; j < Lb.length; j++)
	{ 
		Lc.elem[j+La.length] = Lb.elem[j]; //将Lb元素放在后面
	} 
	return OK;
}

int DeleteValue(List &L, int i, int &e)
{//删除L的第i个数据元素，并用e返回其值，L的长度减1
	e = L.elem[i-1]; //保留删除的元素
	int *q = &(L.elem[i]);//标记第i个元素的位置
	for (; q < &(L.elem[L.length-1]); q++)
	{ 
		*q = *(q+1); //将第i个位置后的元素全部往前移动一位
	}
	L.length--; //表长减1
	return e;
}
	
Status ListPrint(List L)
{//打印线性表的数据元素
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
	printf ("为线性表L1输入10个数字：\n");
	InputValue(L1);
	printf ("L1中的数据元素为：\n");
	ListPrint(L1);
	printf ("排序L1:\n");
	SortValue(L1);
	ListPrint(L1);
	printf ("在L1第五个位置插入新的数据元素100：\n");
	InsertValue(L1, 5, 100);
	ListPrint(L1);
	printf ("再次排序L1：\n");
	SortValue(L1);
	ListPrint(L1);
	List L2, L3;
	InitList(L2);
	printf ("\n为线性表L2输入10个数字：\n");
	InputValue(L2);
	printf ("L2中的数据元素为：\n");
	ListPrint(L2);
	InitList(L3);
	printf ("\n将L1与L2合并到L3中，合并后的L3中的数据元素为：\n");
	MergeList(L1, L2, L3);
	ListPrint(L3);
	printf ("L3的长度为：%d\n", ListLength(L3));
	printf ("排序L3:\n");
	SortValue(L3);
	ListPrint(L3);
	ClearList(L2);
	printf ("重置L2为空表, 检测中...");
	if (ListEmpty(L2))
	{
		printf ("重置成功\n");
	} 
	else
	{ 
		printf ("重置失败\n");
	} 
	printf ("检查L3第15个数据元素...");
	int e;
	printf ("L3第15个数据元素为:%d\n", GetValue(L3, 15, e));
	printf ("正在删除第15个元素%d...", DeleteValue(L3, 15, e));
	printf ("删除完毕，检测L3中此时的数据元素为:\n");
	ListPrint(L3);
	printf ("此时L3的长度为:%d\n", ListLength(L3));
	printf ("\n实验完毕，程序运行正常! :) \n");
	return 0;
}

