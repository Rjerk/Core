#include <stdio.h>
  
int main ()  
{  
    	int n, m, a[1000][3];  
    	int i, j, temp;   
    	scanf ("%d", &n);  
    	while (n--)  
    	{  
		scanf ("%d", &m);  
        	for (i = 1;i <= m; i++)  
        	{  
           	 	scanf ("%d%d%d", &a[i][0], &a[i][1], &a[i][2]); 
			/*同步: 编号 长 宽*/
        	    	if (a[i][1] < a[i][2]) 
			{	
				temp = a[i][1];
				a[i][1] = a[i][2];
				a[i][2] = temp;
			} 
        } 

	/*检验第一组和第二组的数据是否相等，若相等，则将第二组和
        最后一组互换，并删去最后一组.然后检验第三组和第一二组是否
        相等，相等则与最后一组进行互换并删去最后一组，以此类推，
        将多余的长方形全都删去*/
        for (i = 2; i <= m; i++)
	{         
		for(j = 1; j < i; j++)
		{  
                	if (	   a[j][0] == a[i][0] 
			       	&& a[j][1] == a[i][1] 
				&& a[j][2] == a[i][2])  
                	{
				a[i][0]	= a[m][0]; 
				a[i][1] = a[m][1];
				a[i][2] = a[m][2]; 
				m--; 
				i--; 
				break;
			}
		}
	}

	/*冒泡排序*/
        for (i = 1; i <= m; i++)
	{         
            	for (j = m; j > i; j--)
		{  
                	if (a[j][0] < a[i][0] 
			|| (a[j][0] == a[i][0] && a[j][1] < a[i][1]) 
			|| (a[j][0] == a[i][0]
			 && a[j][1] == a[i][1] && a[j][2] < a[i][2]))
                    	{
				temp = a[i][0];
				a[i][0] = a[j][0];
				a[j][0] = temp; 
			 	temp = a[i][1];
				a[i][1] = a[j][1];
				a[j][1] = temp;  
				temp = a[i][2];
				a[i][2] = a[j][2];
				a[j][2] = temp;
			}  
		}   
        }
       	for (i = 1; i <= m; i++)        //打印结果   
            printf ("%d %d %d\n", a[i][0], a[i][1], a[i][2]);  
    } 
    return 0;   
}          
