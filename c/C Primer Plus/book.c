#include <stdio.h>
#define MAXTITL 41 
#define MAXAUTL 31
struct book {
	char title[MAXTITL];
	char author[MAXAUTL];
	float value;
};
int main (void)
{
	struct book library;//把library声明为book类型的变量
	printf ("Please enter the book title.\n");
	gets (library.title);//访问title部分
	printf ("Now enter the author:\n");
	gets (library.author);
	printf ("Now enter the value:\n");
	scanf ("%f", &library.value); 
	printf ("%s by %s: $%0.2f\n", library.title, library.author, 
		library.value);
	printf ("%s: \"%s\" ($%0.2f) \n", library.author, library.title,
	        library.value);
	printf ("Done.\n");
	
	return 0;
}

