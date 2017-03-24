#include<stdio.h>

void aver1(float *b)
{
	int i,j;
	float s=0;
	for(i=0;i<4;i++)
	{  
		s=s+*(b+j);
   		j=j+5;}
        	printf("%f\n",s/4);
     	}
 	void excellent(float (*b)[5])
 	{
      		int n[27]={0},x[27]={0};
      		int i,j=0,k,h=0,f=0;
	      	float w;
       		for(i=0;i<4;i++)
     		{
			h=0,f=0;
			w=0;
     			for(k=0;k<5;k++)
    			{ 	
				w=w+*(*(b+i)+k);
     				if(*(*(b+i)+k)>=85)
      					h++;
      				if(h>=5)
      				printf("da yu ba shi wu student %d\n ",i);
      			}			
      			if((w/5)>=90)
    	 		printf("da yu jiu shi student %d\n",i);
     	 	}
	}	

 	void fail(float (*b)[5])
 	{
   		int n[27],x[27];
   		int i,j=0,k,h=0;
   		float w;
   		for(i=0;i<4;i++)
   		{	
			n[j++]=0;
  			for(k=0;k<5;k++) 
   				if(*(*(b+i)+k)<60.0)
     				{
       	 				n[j]++;
        				if(n[j]>=2)
      					{ 	
						x[h]=i;
      						h++;
      						break;
					}      
                    		}
		}
         	for(i=0;i<h;i++)
         	{
			printf("%d ",x[i]);
         		w=0;
         		for(k=0;k<5;k++)
         		{
         			printf("%.2f\t ",*(*(b+x[i])+k));
        			w=w+*(*(b+x[i])+k);
         		}
         		printf("%.3f\n",w/5);
        	}
}
int main()
{
  	float a[4][5];
  	int i,j,k,b,n;
  	for(i=0;i<4;i++) 
  		for(j=0;j<5;j++)
  			scanf("%f",&a[i][j]);
  	aver1(*a);
  	fail(a);
  	excellent(a);
  	return 0;   
}
