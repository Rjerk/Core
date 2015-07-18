#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
int a[12];
srand((unsigned)time(NULL));
for(int i=0;i<12;i++)
{
a[i]=(rand()%11+5);
printf("%4d",a[i]);
if((i+1)%4==0)
puts("");
}
}

