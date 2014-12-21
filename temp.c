#include <stdio.h>
#include <string.h>

int GetInt(char *prompt)
{
	int num, digits = 0, length = 5;
	char string[length];

	printf("%s", prompt);
	fgets(str, length, stdin);
		
	for(i = 0; i < length; i++)
	{
		if(isdigit(string[i])
		{
			digits++;
		}
	}	
	
	if(digits == length)
	{
		valid == 1;
	}
	else
	{
		valid == 0;
	}
	
	printf("valid = %d", valid);
	
	return (num);
	
}

int main()
{
	int num = GetInt("please enter a number: ");
	
	printf("%d", num);
	
	
	return 0;
}