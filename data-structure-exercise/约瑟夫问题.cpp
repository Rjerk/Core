#include <stdio.h>
#include <stdlib.h>
typedef struct node *link;
struct node
{
        int item;
        link next;
};
int main ()
{
        int N, M;
        scanf ("%d%d", &N, &M);
        link t = (malloc (sizeof *t));
        link x = t;
        x->item = 1; //创建一个代表1号的单节点循环链表
        x->next = x;
        for (int i = 2; i <= N; i++) //将2-N号按序插入链表以建立循环链表
        {
                x = (x->next = malloc(sizeof *x));
                x->item = i;
                x->next = t;
        }
        while (x != x->next)
        {
                for (int i = 1; i < M; i++) //顺着链表遍历数出M-1个元素
                        x = x->next;
                x->next = x->next->next;//删除下一个节点
                N--;
        }
        printf ("%d\n", x->item);
}
