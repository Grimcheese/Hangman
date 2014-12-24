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
		
		printf("The string you entered is: %s", string);
			
		length = strlen(string);
		for(i = 0; i < length - 1; i++)
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
			valid = 1;
			printf("Valid\n");
			
			
			// Convert the string to an integer
			num = 0;
			for(i = 0; i < length - 1; i++)
			{
				num = num * 10;
				num = (num + (int)string[i]) - 48;
			}
			
		}
		else
		{
			valid = 0;
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