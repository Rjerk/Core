#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  MAXBIT  10
#define  MAX  9999999
typedef struct {
    char Code[MAXBIT];
    int  start;
} HuffmanCode;

typedef struct {
    int flag; //In Select:set flag stands for the position have been visited.
    int weight;
    int parent;
    int lchild;
    int rchild;
} HuffmanNode;

//Get two nodes whose weight is smallest in Huffman Tree;
void Select(HuffmanNode *HT, int m, int &s1, int &s2)
{
    //printf ("m = %d....\n", m);
    int min = MAX;
    for (int i = 1; i < m; i++)
    { 
        for (int j = i + 1; j <= m; j++)
		{
            if (HT[i].flag == 0 && HT[j].flag == 0)
			{
                int w1 = HT[i].weight;
                int w2 = HT[j].weight;
                if (w1 + w2 < min)
				{
                    s1 = i;
                    s2 = j;
                    //printf ("i  = %d, j  = %d\n",  i,  j);
                    //printf ("w1 = %d, w2 = %d\n", w1, w2);
                    //printf ("s1 = %d, s2 = %d\n", s1, s2);
                    min = w1 + w2;
                }
            }
        }
    } 
    HT[s1].flag = HT[s2].flag = 1;
}

//Create Huffman Tree
void HuffmanTreeBuilt(HuffmanNode *HT, int n)
{
    int s1, s2;
    for (int i = 1; i <= 2*n-1; i++)
    { 
        HT[i].parent = HT[i].lchild = HT[i].rchild = HT[i].flag = 0;
    } 
    for (int i = 1; i <= n; i++ )
	{
        printf ("Input the weight of the leaf:%d ", i);
        scanf ("%d", &HT[i].weight);
    }
    for (int i = n + 1; i <= 2*n-1; i++)
	{
        Select(HT, i - 1, s1, s2);
        HT[s1].parent = HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
}

//Get Huffman Code
void GetHuffmanCode(HuffmanNode *HT, HuffmanCode *HC, int n)
{
    char cd[n];
    cd[n-1] = '\0';
    for (int i = 1; i <= n; i++)
	{
        HC[i].start = n - 1;
        int chi = i;
        int par = HT[i].parent;
        while (par)
		{
            HC[i].start--;
            if (HT[par].lchild == chi)
            { 
                cd[HC[i].start] = '0';
            } 
            else
            { 
                cd[HC[i].start] = '1';
            } 
            chi = par;
            par = HT[par].parent;
        }
        strcpy(HC[i].Code, &cd[HC[i].start]);
    }
}

//Print HuffmanCode
void PrintHuffmanCode(HuffmanCode *HC, int n)
{
    puts("\nHuffmanCode:");
    for (int i = 1; i <= n; i++)
    { 
        printf ("%s\n", HC[i].Code);
    } 
}

int main(){
    int n;
    printf ("Input number: ");
    scanf ("%d", &n);
    HuffmanNode HT[2*n-1];
    HuffmanCode HC[n];
    HuffmanTreeBuilt(HT, n);
    GetHuffmanCode(HT, HC, n);
    PrintHuffmanCode(HC, n);
    return 0;
}

