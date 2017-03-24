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

//�Ƚ�ָ������ȷ���0�����ȷ���+-1
int CompareExpn(term a, term b)
{
    if (a.expn == b.expn)
        return 0;
    else
        return (a.expn - b.expn) / abs(a.expn - b.expn);
}

//��ָ����С����������
void OrderInsert(Linklist &L, term e, int (*comp)(term, term))
{
    Node pre, current, newnode;
    pre = L; //ǰ��ָ�뿪ʼ��ͷ�ڵ�
    current = pre -> next; //��ǰָ���ڽ���ǰ��ָ��֮��
    while (current && comp(current -> data, e) < 0){ //��ǰָ�벻ΪNULL�ҵ�ǰ�ڵ����ָ��С��Ҫ��������ָ��
        pre = current; //ǰ��ָ��������ǰָ��
        current = current -> next; //��ǰָ��������һ���ڵ�
    }
    newnode = (Node) malloc (sizeof(Node));
    newnode -> data = e;
    pre -> next = newnode; //��ǰ�ڵ�����ָ�����ڻ����Ҫ��������ָ�������ý��½ڵ����pre��current֮��
    newnode -> next = current;
}

//Ѱ����������ָ����ȵ���
int LocateElem(Linklist &L, term e, Node &pre, Node &get, int (*comp)(term, term))
{
    Node current;
    pre = L;
    current = pre -> next;
    while (current && comp(current -> data, e) != 0){ //��ǰָ�벻ΪNULL��ָ��������pre��current������һ���ڵ�
        pre = current;
        current = current -> next;
    }
    if (!current){ //��currentΪNULL˵��δ�ҵ�����0
        current = get = NULL;
        return 0;
    }
    else{
        get = current; //�ҵ���current���ҵ������ָ���get
        return 1;
    }
}

//ɾ��current��ָ�ڵ����һ���ڵ�
void DeleteNext(Linklist &L, Node current)
{
    Node nextnode = current -> next;
    current -> next = nextnode -> next;
    free(nextnode);
}

//�����µ����������Ѱ����ָ֮����ȵ���ҵ�����Ӳ�����DeleteNext, δ�ҵ������OrderInsert��������
void OrderInsertMerge(Linklist &L, term e, int (*comp)(term, term))
{
    Node pre, get;
    if (LocateElem(L, e, pre, get, comp)){
        get -> data.coef += e.coef;
        if (!get -> data.coef) //����Ӻ��ϵ��Ϊ0�򽫴˽ڵ�ɾ��
            DeleteNext(L, pre); //�ô˽ڵ��ǰ��ָ��ɾ���˽ڵ�
    }
    else
        OrderInsert(L, e, comp);
}

//�������������Լ������ֵ������OrderInsertMerge���в������
void CreatePolyn(Linklist &L)
{
    L = (Node) malloc (sizeof(Node)); //����ͷ�ڵ�
    L -> next = NULL;
    int num;
    term e;
    printf ("������һԪ����ʽ������: ");
    scanf ("%d", &num);
    printf ("������ϵ����ָ�����ÿո���\n");
    for(; num > 0; num--){
        scanf ("%f%d", &e.coef, &e.expn);
        while (e.coef == 0){
            printf ("ϵ������0�� �������������!\n");
            scanf ("%f%d", &e.coef, &e.expn);
        }
        OrderInsertMerge(L, e, CompareExpn);
    }
}

//��ӡ�����ֵ(���������ʽ)
//���ڶ���ʽ�ĵ�һ��ǰ�治������Ӻţ����ó������������
//�������������а���ָ����С���к�ָ��Ϊ0�����ֻ��������Ԫ��� ���ʼ����ж�ָ��Ϊ0�Ĳ���
//�������������ϵ��Ϊ +1 �� -1 ����ֻ���ָ�����֣�����ָ��Ϊ0����ֻ���ϵ�����֡�
void PrintPolyn(Linklist &L)
{
    Node current = L -> next;
    printf ("��һԪ����ʽΪ:  ");
    if (current -> data.coef == 1)
        if (current -> data.expn != 0) //����Ԫ���ϵ��Ϊ1ָ����Ϊ0����ֻ���ָ������
            printf ("x^%d", current -> data.expn);
        else
            printf ("1"); //����Ԫ���ϵ��Ϊ1ָ��Ϊ0�������1

    else if (current -> data.coef == -1)
        if (current -> data.expn != 0) //����Ԫ���ϵ��Ϊ-1ָ����Ϊ0����ֻ���ָ������
            printf ("-x^%d", current -> data.expn);
        else
            printf ("-1"); //����Ԫ���ϵ��Ϊ1ָ��Ϊ0�������-1

    else
        if (current -> data.expn != 0) //����Ԫ���ָ����Ϊ0�������ȫ��
            printf ("%.1fx^%d", current -> data.coef, current -> data.expn);
        else
            printf ("%.1f", current -> data.coef); //����Ԫ���ָ��Ϊ0����ֻ���ϵ��

    current = current -> next;
    while (current){
        //�ӵڶ��ʼ����ϵ������0��ǰ�����'+'��Ϊ����֮����νӣ���С��0��ԭ�����ϵ��
        if (current -> data.coef >0)
            if (current -> data.coef == 1)
                printf (" + x^%d", current -> data.expn);//ϵ��Ϊ1���ָ��
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

////��ӡ�����ֵ(���������ʽ)
//void PrintPolyn(Linklist &L){
//    Node current = L -> next; //��ǰָ��ָ����Ԫ�ڵ�
//    printf ("ϵ��   ָ��\n");
//    while (current){
//        printf ("%3.2f   %d\n", current -> data.coef, current -> data.expn);
//        current = current -> next; //ָ����һ���ڵ�
//    }
//}


//������Ӳ���
void Add(Linklist &L1, Linklist L2, Linklist &L3)
{
    L3 = L1;
    Node L2node;
    L2node = L2 -> next;
    while (L2node){
        OrderInsertMerge(L3, L2node -> data, CompareExpn); //��L2�еĸ������L1�в����кϲ�����
        L2node = L2node -> next;
    }
}

//������˲���
void Multify(Linklist L1, Linklist L2, Linklist &L3)
{
    L3 = (Node) malloc (sizeof(Node)); //����L3�洢����
    L3 -> next = NULL;
    Node L1node = L1 -> next, L2node = L2 -> next; //����ָ����Ԫ�ڵ�
    term Newterm;
    for (; L1node != NULL; L1node = L1node -> next){
        for (; L2node != NULL; L2node = L2node -> next){
            Newterm.coef = L1node -> data.coef * L2node -> data.coef; //ϵ�����
            Newterm.expn = L1node -> data.expn + L2node -> data.expn; //ָ�����
            OrderInsertMerge(L3, Newterm, CompareExpn); //�������L3
        }
        L2node = L2 -> next; //ÿ�ζ�L2������г˷��������ֻص�L2����Ԫ�ڵ㣬��L1����һ��������г˷�����
    }
}

int main (){
    Linklist La, Lb, Lc;
    printf ("��һ��һԪ����ʽ:\n");
    CreatePolyn(La);
    PrintPolyn(La);
    printf ("\n�ڶ���һԪ����ʽ:\n");
    CreatePolyn(Lb);
    PrintPolyn(Lb);
    //printf ("\n����һԪ����ʽ���:\n");
    //Add(La, Lb, Lc);
    //PrintPolyn(Lc);
    Multify(La, Lb, Lc);
    printf ("����һԪ����ʽ���:\n");
    PrintPolyn(Lc);
    return 0;
}

