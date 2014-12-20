#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
	char* c;	  // pointer to the string
	int size = 5; // size of the word + null character
	int i;	
	//printf("The size of the char is: %d", sizeof(*c));
	
	c = malloc(size);
	
	strcpy(c, "hello there");
	//c[size - 1] = '\0';
	
	printf("%s\n", c);
	
	for(i = 0; i  < 10; i++)
	{
		printf("%c\n", c[i]);
	}
	/*
	str = (char *) malloc(size);
	
	bsize = sizeof(str);
	printf("%d\n", bsize);
	
	strcpy(str, "the string");
	
	printf("%s \n", str);
	*/
	return 0;

}
