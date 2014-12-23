#include <stdio.h>
#include <ctype.h>

int main()
{
	char letter;
	int d;
	
	scanf("%c", &letter);
	
	d = isdigit(letter);
	
	if(d != 0)
	{
		printf("is a digit");
	}
	
	return 0;
}