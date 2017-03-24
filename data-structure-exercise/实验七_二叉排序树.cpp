/*
编写算法实现二叉排序树的创建，插入与删除操作。
（创建时是根据给定数据的无序序列，按照输入顺序创建）
*/
#include <stdio.h>
#include <stdlib.h>
const int ENDFLAG = -1;

typedef struct node {
    int data;
    struct node *lchild;
    struct node *rchild;
    struct node *parrent;
} Node, *Tree;

//非递归插入节点
void InsertBST_nonrecursive(Tree &T, int e)
{
    Node *newnode = (Node *) malloc (sizeof(Node));
    if (newnode == NULL){
        exit(0);
    }
    newnode->data =e;
    newnode->rchild = newnode->lchild = NULL;
    Node *find = T;
    Node *parrent = NULL;

    while (find != NULL) {
        parrent = find;
        find = (e < find->data ?
            find->lchild : find->rchild);
    }

    if (parrent == NULL) {
        T = newnode;
    }
    else {
        if (e < parrent->data){
            parrent->lchild = newnode;
        }
        else{
            parrent->rchild = newnode;
        }
    }
    newnode->parrent = parrent;
}

//创建二叉查找树
void CreateBST(Tree &T, int a[])
{
    T = NULL;
    for (int i = 0; a[i] != ENDFLAG; i++){
        InsertBST_nonrecursive(T, a[i]);
    }
}

//递归查找
Tree Search_BST_recursive(Tree T, int key)
{
    if (T == NULL || key == T->data) {
        return T;
    }
    else {
        return key < T->data ?
            Search_BST_recursive(T->lchild, key)
          : Search_BST_recursive(T->rchild, key);
    }
}

//非递归查找
Tree Search_BST_nonrecursive(Tree  T, int key)
{
    while (T != NULL && T->data != key){
        if (key < T->data){
            T = T->lchild;
        }
        else{
            T = T->rchild;
        }
    }
    return T;
}

//最小值
Tree TreeMinimum(Tree T)
{
    while (T->lchild != NULL){
        T = T->lchild;
    }
    return T;
}

//最大值
Tree TreeMaximum(Tree T)
{
    while (T->rchild != NULL){
        T = T->rchild;
    }
    return T;
}

//中序后继
Tree Successor(Tree x)
{
    if (x->rchild != NULL){
        return TreeMinimum(x->rchild);
    }
    else if (x == x->parrent->lchild){
        return x->parrent;
    }
    else{
        Node *s = x->parrent;
        while (s != NULL && x == s->rchild){
            x = s;
            s = s->parrent;
        }
    return s;
    }
}

//中序前驱
Tree Predecessor(Tree x)
{
    if (x->lchild != NULL) {
        return TreeMaximum(x->lchild);
    }
    else if (x == x->parrent->rchild) {
        return x->parrent;
    }
    else if (x == x->parrent->lchild) {
        Node *s = x->parrent;
        while (s != NULL && x == s->lchild){
            x = s;
            s = s->parrent;
        }
        return s;
    }
    return x;
}

//删除节点
void Delete(Tree &T, int e)
{
    Node *find = T;
    Node *find_parrent = NULL;
    while (find){ //Find the node whose data is e
        if (find->data == e){
            break;
        }
        find_parrent = find;
        find = (find->data > e ? find->lchild : find->rchild);
    }
    if (find == NULL){
        puts ("Not found !");
        return ;
    }
    Node *q;
    if (find->lchild != NULL && find->rchild != NULL){
    //方法1.找到要被删除节点的后继节点，让其父节点成为其右子树的父节点
    //（后继节点一定无左子树），并用其值代替被删除的节点
    ///*
        Node *successor = Successor(find);
        find->data = successor->data;
        if (successor == successor->parrent->rchild) {
            successor->parrent->rchild = successor->rchild;
        }
        else {
            successor->parrent->lchild = successor->rchild;
        }
        free(successor);
        find = NULL;
        return ;
    //*/
    //方法2.找到要被删除节点的前驱节点，让其父节点成为其左子树的父节点
    //（前驱节点一定无右子树），并用其值代替被删除的节点
    /*
        Node *predecessor = Predecessor(find);
        find->data = predecessor->data;
        if (predecessor == predecessor->parrent->rchild){
            predecessor->parrent->rchild = predecessor->lchild;
        }
        else {
            predecessor->parrent->lchild = predecessor->lchild;
        }
        free(predecessor);
        find = NULL;
        return ;
    */
    }
    else if (find->rchild == NULL){
        q = find;
        find = find->lchild;
    }
    else if (find->lchild == NULL){
        q = find;
        find = find->rchild;
    }
    if (find_parrent == NULL){
        T = find;
    }
    else if (q == find_parrent->rchild){
        find_parrent->rchild = find;
    }
    else {
        find_parrent->lchild = find;
    }
    free(q);
}

//中序遍历二叉树
void InOrderTreeWalk(Tree T)
{
    if (T != NULL) {
        InOrderTreeWalk(T->lchild);
        printf ("%d ", T->data);
        InOrderTreeWalk(T->rchild);
    }
}

int main()
{
    Tree T;
    int a[100] = {19, 17, 29, 12, 18, 22, 33, 6, 13, 21, 25, 16, 15, -1};
    CreateBST(T, a);
    printf ("\nInOrderTreeWalk: ");
    InOrderTreeWalk(T);
    Node *flag = NULL;
    int num;
    printf ("\nInput the number you want to find: ");
    scanf ("%d", &num);
    flag = Search_BST_nonrecursive(T, num);
    if (flag == NULL) {
        printf ("\nNot Found\n");
        return 0;
    }
    else {
        printf ("Find it!\n");
    }
    Node *find = Predecessor(flag);
    if (find != NULL){
        printf ("The Predecessor is: %d", find->data);
    }
    else {
        printf ("No Predecessor");
    }
    find = Successor(flag);
    if (find != NULL){
        printf ("\nThe Successor is: %d", find->data);
    }
    else {
        printf ("\nNo Successor");
    }
    printf ("\nInput the number you want to delete: ");
    scanf ("%d", &num);
    flag = Search_BST_nonrecursive(T, num);
    if (flag == NULL){
        printf ("\nNot Found");
    }
    else {
        Delete(T, num);
        printf ("\nAfter delete %d: ", num);
        printf ("\nInOrderTreeWalk: ");
        InOrderTreeWalk(T);
    }
    puts ("");
    return 0;
}

