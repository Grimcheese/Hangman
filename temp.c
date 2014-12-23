#include <stdio.h>
#include <string.h>
#include <ctype.h>

# define LENGTH 10

int GetInt(char *prompt)
{
	int i, num, valid, digit, length;
	char string[10];
	do
	{
		printf("%s", prompt);
		fgets(string, 10, stdin);
			
		length = strlen(string);
		for(i = 0; i < length; i++)
		{
			if((isdigit(string[i]) != 0))
			{
				digit = 1;
			}
			else
			{
				digit = 0;
				break;
			}
		}	
		
		if(digit == 1)
		{
			valid == 1;
			printf("Valid\n");
			
			for(i = 0; i < length; i++);
		}
		else
		{
			valid == 0;
			printf("Not Valid\n");
		}
	}while(valid == 0);
	
	
	return (num);
	
}

int main()
{
	int num = GetInt("please enter a number: ");
	
	printf("%d", num);
	
	
	return 0;
}