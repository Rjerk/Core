#include <stdio.h>
#include <stdlib.h>
const int MVNUM = 100;
const int STACK_INIT_SIZE = 10;
const int STACK_INCREMENT = 10;
const int QUEUESIZE = 100;
bool visited[MVNUM] = {false};
int indegree[MVNUM] = {0};
char topo[MVNUM];

typedef struct ArcNode {
    char adjvex;
    struct ArcNode *nextarc;
} ArcNode;

typedef struct Vnode {
    char firstvex;
    ArcNode *firstarc;
} Vnode, Adjlist[MVNUM];

typedef struct {
    Adjlist vertices;
    int vexnum;
    int arcnum;
} AlGraph;

typedef struct {
	char *base;
    int front;
    int rear;
    int length;
} Queue;

typedef struct {
    int *top;
    int *base;
    int stacklength;
    int stacksize;
} Stack;

void InitQueue(Queue &Q)
{
    Q.base = (char *) malloc (sizeof(char) * QUEUESIZE);
    if (Q.base == NULL)
    {
        exit(0);
    }
    Q.front = Q.rear = 0;
    Q.length = 0;
}

bool EmptyQueue(Queue Q)
{
    return (Q.front == Q.rear ? true : false);
}

bool FullQueue(Queue Q)
{
    return (Q.length == QUEUESIZE ? true : false);
}

void EnQueue(Queue &Q, char v)
{
    if (FullQueue(Q))
    {
        puts ("Queue is full\n");
        exit(1);
    }
    else
    {
        Q.base[Q.rear++] = v;
        //printf ("\nEnQueue = %c", v);
        Q.length++;
    }
}

void DeQueue(Queue &Q, char &v)
{
    if (EmptyQueue(Q))
    {
        puts ("Queue is empty\n");
        exit(2);
    }
    else
    {
        v = Q.base[Q.front++];
        //printf ("\nDeQueue = %c", v);
        Q.length--;
    }
}

/*void PrintQueue(Queue Q){
    printf ("\nThe current queue is: ");
    while (!EmptyQueue(Q))
    {
        printf ("%c ", Q.base[Q.front++]);
    }
    puts("");
}*/

void InitStack(Stack &S)
{
    S.top = S.base = (int *) malloc (sizeof(int) * STACK_INIT_SIZE);
    if (!S.top){
        printf ("Stack memory allocation wrongs!\n");
        exit(0);
    }
    S.stacklength = 0;
    S.stacksize = STACK_INIT_SIZE;
}

void Realloc(Stack &S)
{
    S.base = (int *) realloc (S.base,
            (S.stacksize + STACK_INCREMENT) * sizeof(int));
    if (!S.base){
        printf ("Stack reallocation wrongs!\n");
        exit(1);
    }
    S.top = S.base + S.stacksize;
    S.stacksize += STACK_INCREMENT;
}

bool FullStack(Stack S)
{
    if (S.stacklength == S.stacksize)
        return true;
    return false;
}

bool EmptyStack(Stack S)
{
    if (S.top == S.base)
        return true;
    return false;
}

void Push(Stack &S, int e)
{
    if (FullStack(S))
        Realloc(S);
    *(S.top++) = e;
}

void Pop(Stack &S, int &e)
{
    if (EmptyStack(S)){
        printf ("Stack is empty\n");
        exit(2);
    }
    e = *(--S.top);
}

/*void PrintStack(Stack S){
    int *print = S.top;
    while (print != S.base){
        printf ("%d\n", *(--print));
    }
}*/

//查找点v的下标 
int Locate(AlGraph G, char v)
{  
    for (int i = 0; i < G.vexnum; i++)
    {
        if (v == G.vertices[i].firstvex)
        {
            return i;
        }
    }
}

//创建无向图 
/*void CreateUDG(AlGraph &G)
{
    puts ("-----------Create a UDG-----------");
	printf ("Input vexnum and arcnum: ");
    scanf ("%d%d", &G.vexnum, &G.arcnum); //输入点数和边数 
    printf ("Input all vertices: ");
    getchar();
    for (int i = 0; i < G.vexnum; i++)
    {
         scanf ("%c", &G.vertices[i].firstvex); //输入所有点 
         getchar();
         G.vertices[i].firstarc = NULL;
         visited[i] = false;
    }
    char v1, v2;
    int i, j;
    for (int k = 0; k < G.arcnum; k++)
    {
        printf ("Input two virtices of an edge: ");
        scanf ("%c %c", &v1, &v2); //输入一条边对应的两点 
        getchar();
        i = Locate(G, v1);
        j = Locate(G, v2);

 		//构造邻接表
        ArcNode *p1 = (ArcNode *) malloc (sizeof(ArcNode)); 
        p1->adjvex = v1;
        p1->nextarc = G.vertices[j].firstarc;
        G.vertices[j].firstarc = p1;

        ArcNode *p2 = (ArcNode *) malloc (sizeof(ArcNode));
        p2->adjvex = v2;
        p2->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p2;
    }
}*/

void Sort(AlGraph &G) //冒泡排序 
{
	for (int i = 0; i < G.vexnum; i++)
	{
		ArcNode *p1 = G.vertices[i].firstarc, *p2; //p1指向首元结点 
 		char  tmp; 
 		if (p1 != NULL){
	 		for (; p1 -> nextarc != NULL; p1 = p1 -> nextarc)
			{
	 			p2 = p1 -> nextarc; //p2指向p1之后结点 
	 			for ( ; p2 != NULL; p2 = p2 -> nextarc)
				{
	 				if (p1->adjvex > p2->adjvex)
					{ 
	 					tmp = p1 -> adjvex;
	 					p1 -> adjvex = p2 -> adjvex;
	 					p2 -> adjvex = tmp;
	 				}
	 			}
	 		}
	 	}
	}
}
//创建有向图 
void CreateDG(AlGraph &G)
{
    printf ("输入点和边的数量: ");
    scanf ("%d%d", &G.vexnum, &G.arcnum);
    printf ("输入所有的点: ");
    getchar();
    for (int i = 0; i < G.vexnum; i++)
    {
         scanf ("%c", &G.vertices[i].firstvex);
         getchar();
         G.vertices[i].firstarc = NULL;
    }
    char v1, v2;
    int i, j;
    for (int k = 0; k < G.arcnum; k++)
    {
        printf ("输入有向边: ");
        scanf ("%c %c", &v1, &v2);
        getchar();
        i = Locate(G, v1);
        j = Locate(G, v2);

        ArcNode *p = (ArcNode *) malloc (sizeof(ArcNode));
        p->adjvex = v2;
        p->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p;
    }
}

//打印邻接表 
void PrintAdjList(AlGraph G)
{
    puts ("有向图的邻接表: ");
    for (int i = 0; i < G.vexnum; i++)
    {
        ArcNode *print = G.vertices[i].firstarc;
        printf ("%c ", G.vertices[i].firstvex);
        while (print != NULL)
        {
            printf ("%c ", print->adjvex);
            print = print->nextarc;
        }
        puts ("");
    }
}
void FindDegree(AlGraph G, int* indegree)
{
    int find = G.vexnum;
    for (int i = 0; i < G.vexnum; i++)
    {
        int degree = 0;
        for (int j = 0; j < G.vexnum; j++)
        {
            if (j != i)
            {
                ArcNode *p = G.vertices[j].firstarc;
                char findAdjvex = G.vertices[i].firstvex;
                while (p != NULL)
                {
                    if (p->adjvex == findAdjvex)
                    {
                        degree++;
                    }
                    p = p->nextarc;
                }
            }
            else
            {
                continue;
            }
            indegree[i] = degree;
        }
    }
}

/*void PrintDegree(AlGraph G, int* indegree)
{
    FindDegree(G, indegree);
    printf ("indegree[%d] = [", G.vexnum);
    for (int i = 0; i < G.vexnum; i++)
    {
        printf ("%d ", indegree[i]);
    }
    puts ("]");
}*/

void TopologicalSort(AlGraph G, char topo[])
{
    Stack S;
    int i, m;
    FindDegree(G, indegree);
    InitStack(S);
    for (i = 0; i < G.vexnum; i++)
    {
        if (!indegree[i])
        {
            Push(S, i);
        }
    }
    m = 0;
    while (!EmptyStack(S))
    {
        Pop(S, i);
        topo[m++] = G.vertices[i].firstvex;
        ArcNode *p = G.vertices[i].firstarc;
        while (p != NULL)
        {
            char findvex = p->adjvex;
            int num = Locate(G, findvex);
            indegree[num]--;
            if (indegree[num] == 0)
            {
                Push(S, num);
            }
            p = p->nextarc;
        }
    }
    if (m < G.vexnum)
    {
        puts ("\n拓扑排序失败");
    }
    else
    {
        puts ("\n拓扑排序成功");
    }

}

void BFS(AlGraph G, int start)
{
    puts ("\n广度优先搜索: ");
    visited[start] = true;
    char vex = G.vertices[start].firstvex;
    Queue Q;
    InitQueue(Q);
    EnQueue(Q, vex);
    while (!EmptyQueue(Q))
    {
        DeQueue(Q, vex); //出队后打印点 
        printf ("%c ", vex);
        int pos = Locate(G, vex);
        ArcNode *p = G.vertices[pos].firstarc;
        while (p != NULL)
        {
        	//寻找所有邻接点 
            int num = Locate(G, p->adjvex);
            if (!visited[num]) //邻接点未访问则入队 
            {
                visited[num] = true;
                EnQueue(Q, p->adjvex);
            }
            p = p->nextarc;
        }
    }
    puts ("");
}

void DFS(AlGraph G, int start)
{
    visited[start] = true;
    printf ("%c ", G.vertices[start].firstvex);
    ArcNode *p = G.vertices[start].firstarc;
    while (p != NULL)
    {
        int num = Locate(G, p->adjvex);
        if (!visited[num])
        {
            DFS(G, num);
        }
        p = p->nextarc;
    }
}

void DFS_AL(AlGraph G, int start)
{
    for (int i = 0; i < G.vexnum; i++)
    {
        visited[i] = false;
    }
    DFS(G, start);
    puts ("");
}

/* 输入实例
输入点和边的数量：5 6 				输入点和边的数量：5 6
输入所有的点：a b c d e 			输入所有的点：a b c d e
输入有向边: a b						输入有向边: a d
输入有向边: a c						输入有向边: a e
输入有向边: b c						输入有向边: b c
输入有向边: b d						输入有向边: b d
输入有向边: d e 					输入有向边: d a
输入有向边: e c						输入有向边: c a
有向图的邻接表:						有向图的邻接表:
a b c								a d e
b c d								b c d
c									c a
d e									d a
e c 								e

广度优先搜索：						广度优先搜索：
a c b d e							a d e
深度优先搜索:						深度优先搜索:
a c b d e  							a d e

拓扑排序成功    					拓扑排序失败
*/
int main(){
    AlGraph G;
    CreateDG(G);
    Sort(G); 
    PrintAdjList(G);
    BFS(G, 0); //从下标为0的点开始访问 
    puts ("深度优先搜索:");
    DFS_AL(G, 0);
    TopologicalSort(G, topo);
	return 0;
}

