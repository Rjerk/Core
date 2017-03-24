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
int CompareExpn(term a, term b)
{
    if (a.expn == b.expn)
        return 0;
    else
        return (a.expn - b.expn) / abs(a.expn - b.expn);
}

//按指数从小到大插入各项
void OrderInsert(Linklist &L, term e, int (*comp)(term, term))
{
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
int LocateElem(Linklist &L, term e, Node &pre, Node &get, int (*comp)(term, term))
{
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
void DeleteNext(Linklist &L, Node current)
{
    Node nextnode = current -> next;
    current -> next = nextnode -> next;
    free(nextnode);
}

//插入新的项并在链表里寻找与之指数相等的项，找到则相加并调用DeleteNext, 未找到则调用OrderInsert正常插入
void OrderInsertMerge(Linklist &L, term e, int (*comp)(term, term))
{
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
void CreatePolyn(Linklist &L)
{
    L = (Node) malloc (sizeof(Node)); //创建头节点
    L -> next = NULL;
    int num;
    term e;
    printf ("请输入一元多项式的项数: ");
    scanf ("%d", &num);
    printf ("请输入系数和指数，用空格间隔\n");
    for(; num > 0; num--){
        scanf ("%f%d", &e.coef, &e.expn);
        while (e.coef == 0){
            printf ("系数出现0， 请重新输入此项!\n");
            scanf ("%f%d", &e.coef, &e.expn);
        }
        OrderInsertMerge(L, e, CompareExpn);
    }
}

//打印各项的值(横向输出方式)
//对于多项式的第一项前面不必输出加号，故拿出来单独输出。
//而且由于链表中按照指数大小排列后，指数为0的情况只出现在首元结点 ，故加入判断指数为0的部分
//此输出函数对于系数为 +1 或 -1 的项只输出指数部分，对于指数为0的项只输出系数部分。
void PrintPolyn(Linklist &L)
{
    Node current = L -> next;
    printf ("该一元多项式为:  ");
    if (current -> data.coef == 1)
        if (current -> data.expn != 0) //若首元结点系数为1指数不为0，则只输出指数部分
            printf ("x^%d", current -> data.expn);
        else
            printf ("1"); //若首元结点系数为1指数为0，则输出1

    else if (current -> data.coef == -1)
        if (current -> data.expn != 0) //若首元结点系数为-1指数不为0，则只输出指数部分
            printf ("-x^%d", current -> data.expn);
        else
            printf ("-1"); //若首元结点系数为1指数为0，则输出-1

    else
        if (current -> data.expn != 0) //若首元结点指数不为0，则输出全部
            printf ("%.1fx^%d", current -> data.coef, current -> data.expn);
        else
            printf ("%.1f", current -> data.coef); //若首元结点指数为0，则只输出系数

    current = current -> next;
    while (current){
        //从第二项开始，若系数大于0则前面加上'+'作为各项之间的衔接，若小于0则原样输出系数
        if (current -> data.coef >0)
            if (current -> data.coef == 1)
                printf (" + x^%d", current -> data.expn);//系数为1输出指数
            else
                printf (" + %.1fx^%d", current -> data.coef, current -> data.expn);

        else
            if (current -> data.coef == -1)
                printf (" - x^%d", current -> data.expn);
            else
                printf (" %.1fx^%d", current -> data.coef, current -> data.expn);
        current = current -> next;
    }
    printf ("\n");
}

////打印各项的值(纵向输出方式)
//void PrintPolyn(Linklist &L){
//    Node current = L -> next; //当前指针指向首元节点
//    printf ("系数   指数\n");
//    while (current){
//        printf ("%3.2f   %d\n", current -> data.coef, current -> data.expn);
//        current = current -> next; //指向下一个节点
//    }
//}


//各项相加操作
void Add(Linklist &L1, Linklist L2, Linklist &L3)
{
    L3 = L1;
    Node L2node;
    L2node = L2 -> next;
    while (L2node){
        OrderInsertMerge(L3, L2node -> data, CompareExpn); //将L2中的各项插入L1中并进行合并操作
        L2node = L2node -> next;
    }
}

//各项相乘操作
void Multify(Linklist L1, Linklist L2, Linklist &L3)
{
    L3 = (Node) malloc (sizeof(Node)); //创建L3存储各项
    L3 -> next = NULL;
    Node L1node = L1 -> next, L2node = L2 -> next; //各自指向首元节点
    term Newterm;
    for (; L1node != NULL; L1node = L1node -> next){
        for (; L2node != NULL; L2node = L2node -> next){
            Newterm.coef = L1node -> data.coef * L2node -> data.coef; //系数相乘
            Newterm.expn = L1node -> data.expn + L2node -> data.expn; //指数相加
            OrderInsertMerge(L3, Newterm, CompareExpn); //新项插入L3
        }
        L2node = L2 -> next; //每次对L2各项进行乘法操作后又回到L2的首元节点，对L1的下一项继续进行乘法操作
    }
}

int main (){
    Linklist La, Lb, Lc;
    printf ("第一个一元多项式:\n");
    CreatePolyn(La);
    PrintPolyn(La);
    printf ("\n第二个一元多项式:\n");
    CreatePolyn(Lb);
    PrintPolyn(Lb);
    //printf ("\n两个一元多项式相加:\n");
    //Add(La, Lb, Lc);
    //PrintPolyn(Lc);
    Multify(La, Lb, Lc);
    printf ("两个一元多项式相乘:\n");
    PrintPolyn(Lc);
    return 0;
}

