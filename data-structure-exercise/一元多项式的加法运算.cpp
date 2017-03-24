#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float coef;
    int expn;
} term;

typedef struct node {
    term data;
    node *next;
} *Node, *Linklist;

//比较指数，相等返回0，不等返回+-1
int CompareExpn(term a, term b){
    if (a.expn == b.expn)
        return 0;
    else
        return (a.expn - b.expn) / abs(a.expn - b.expn);
}

//按指数从小到大插入各项
void OrderInsert(Linklist &L, term e, int (*comp)(term, term)){
    Node pre, current, newnode;
    pre = L; //前驱指针开始在头节点
    current = pre -> next; //当前指针在紧随前驱指针之后
    while (current && comp(current -> data, e) < 0){ //当前指针不为NULL且当前节点项的指数小于要插入的项的指数
        pre = current; //前驱指针移至当前指针
        current = current -> next; //当前指针移至下一个节点
    }
    newnode = (Node) malloc (sizeof(Node));
    newnode -> data = e;
    pre -> next = newnode; //当前节点的项的指数大于或等于要插入的项的指数，故用将新节点插入pre与current之间
    newnode -> next = current;
}

//寻找与给出项的指数相等的项
int LocateElem(Linklist &L, term e, Node &pre, Node &get, int (*comp)(term, term)){
    Node current;
    pre = L;
    current = pre -> next;
    while (current && comp(current -> data, e) != 0){ //当前指针不为NULL且指数不等则将pre与current移至下一个节点
        pre = current;
        current = current -> next;
    }
    if (!current){ //若current为NULL说明未找到返回0
        current = get = NULL;
        return 0;
    }
    else{
        get = current; //找到则将current即找到的项的指针给get
        return 1;
    }
}

//删除current所指节点的下一个节点
void DeleteNext(Linklist &L, Node current){
    Node nextnode = current -> next;
    current -> next = nextnode -> next;
    free(nextnode);
}

//插入新的项并在链表里寻找与之指数相等的项，找到则相加并调用DeleteNext, 未找到则调用OrderInsert正常插入
void OrderInsertMerge(Linklist &L, term e, int (*comp)(term, term)){
    Node pre, get;
    if (LocateElem(L, e, pre, get, comp)){
        get -> data.coef += e.coef;
        if (!get -> data.coef) //若相加后的系数为0则将此节点删除
            DeleteNext(L, pre); //用此节点的前驱指针删除此节点
    }
    else
        OrderInsert(L, e, comp);
}

//用于输入项数以及各项的值并调用OrderInsertMerge进行插入操作
void CreatePolyn(Linklist &L){
    L = (Node) malloc (sizeof(Node)); //创建头节点
    L -> next = NULL;
    int num;
    term e;
    printf ("请输入一元多项式的项数: ");
    scanf ("%d", &num);
    printf ("请输入系数和指数，用空格间隔\n");
    for (; num > 0; num--){
        scanf ("%f%d", &e.coef, &e.expn);
        OrderInsertMerge(L, e, CompareExpn);
    }
}

//打印各项的值
void PrintPolyn(Linklist &L){
    Node current = L -> next; //当前指针指向首元节点
    printf ("系数   指数\n");
    while (current){
        printf ("%3.2f   %d\n", current -> data.coef, current -> data.expn);
        current = current -> next; //指向下一个节点
    }
}

void Add(Linklist &L1, Linklist L2){
    Node L2node;
    term L2term;
    L2node = L2 -> next;
    while (L2node){
        L2term = L2node -> data;
        OrderInsertMerge(L1, L2term, CompareExpn);
        L2node = L2node -> next;
    }
}

int main (){
    Linklist La, Lb;
    printf ("第一个一元多项式:\n");
    CreatePolyn(La);
    PrintPolyn(La);
    printf ("第二个一元多项式:\n");
    CreatePolyn(Lb);
    PrintPolyn(Lb);
    printf ("两个一元多项式相加:\n");
    Add(La, Lb);
    PrintPolyn(La);
    return 0;
}
