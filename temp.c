#include <stdio.h>
#include <string.h>

int main()
{
	char string[10] = {'\0'};
	char temp[10] = {'\0'};
	
	int index, i;
	strcpy(string, "helloblah");
	
	index = 5;
	for(i = index - 1; i < 10; i++)
	{
		temp[i - index - 1] = string[i];
	}
	
	for(i = 0; i < 10; i++)
	{
		printf("%c", string[i]);
	}
	
	printf("\n");
	
	for(i = 0; i < 10; i++)
	{
		printf("%c", temp[i]);
	}
	
	return 0;
}