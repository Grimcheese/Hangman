#include "header/input.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

/*
	Prompts the user for an integer value and returns that value.
	
	The value entered is input as a string and checked to see if it is
	actually an integer. Only values that are integers are returned.
*/
int GetInt(char *prompt)
{
	int num, chRead, valid;
	
	valid = 0;
	do
	{
		printf("%s", prompt);
		chRead = scanf("%d", &num);
		
		if(chRead != 1)
		{
			printf("Invalid");
		}
		else
		{
			valid = 1;
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
		getchar();
		letter = getchar();
		
		if(letter == '\n')
		{
			printf("Not a valid character: ");
		}
	}while(letter == '\n');
	
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