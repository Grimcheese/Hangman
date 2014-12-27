#include "header/input.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>


#define MAX_SIZE 20
/*
	Prompts the user for an integer value and returns that value.
	
	The value entered is input as a string and checked to see if it is
	actually an integer. Only values that are integers are returned.
	
	n = the highest number of digits in the integer that is to be 
	returned.
*/
int GetInt(char *prompt, int n)
{
	int i, num, valid, digit, length;
	char string[MAX_SIZE], ch;
	
	printf("%s", prompt);
	do
	{
		
		fgets(string, MAX_SIZE, stdin);
		
		
		//while ((ch = getchar()) != '\n' && ch != EOF);
		
		// length - new line char
		length = strlen(string) - 1;
		
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
		
		if(digit == 0)
		{
			printf("Not a number. Try again: ");
			valid = 0;
		}
		else if((string[0] == '0' && length > 1) || string[0] == '\n')
		{
			printf("Incorrect input. Try again: ");
			valid = 0;
		}
		else if(length > n)
		{
			printf("Number has too many digits. Number of digits must be %d or lower\nTry Again: ", n);
			valid = 0;
		}
		else if(digit == 1)
		{
			valid = 1;
			
			// Convert the string to an integer
			num = 0;
			for(i = 0; i < length; i++)
			{
				num = num * 10;
				num = (num + (int)string[i]) - 48;
			}
		}
	}while(valid == 0);
	
	
	return (num);
	
}

/*
	Prompts the user for a character and returns that character to
	the calling function
*/
char GetChar(char *prompt)
{
	char letter;

	printf("%s", prompt);
	
	do
	{
		// get a character and ignore the new line character
		letter = getchar();
		getchar();
		
		if(letter == '\n')
		{
			printf("Not a valid character: ");
		}
	}while(letter != '\n');
	
	return(letter);
}

/*
	Checks a character to see if it is either 'y' or 'n' ignoring case
	
	0 is returned if invalid and 1 is returned if valid
*/
int YNCharCheck(char inChar)
{
	int valid;
	
	inChar = tolower(inChar);
	if(inChar == 'n' || inChar == 'y')
	{
		valid = 1;
	}
	else
	{
		valid = 0;
	}
	
	return(valid);
}