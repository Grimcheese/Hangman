/*
	Hangman game
	
	Daily Programmer Challenge
	
	Game picks a word and lets user guess letters of the word until out
	of turns or the whole word is discovered
	
*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "../libs/input.h"

#define MAX_SIZE 11


// Function prototypes
void Startup(int*, int*);
int GetDifficulty(void);
void PickWord(char[], FILE *);
void debug(char[], int);
FILE *OpenList(int, FILE *);
void PlayGame(char[], int, int);
int DisplayMenu(void);
void DisplaySettings(int, int);
void ChangeConfig(int*, int*);
char GuessLetter(char[]);
int CharacterCount(char, const char[], const int);

int main()
{
	char word[MAX_SIZE];
	int difficulty, turns, choice;

	Startup(&difficulty, &turns);
	
	do
	{
		choice = DisplayMenu();
		
		switch(choice)
		{
			case 0: // Exit game
				printf("Goodbye");
				break;
			case 1: // Begin playing the game
				PlayGame(word, turns, difficulty);
				break;
			case 2: // Enter game config
				DisplaySettings(difficulty, turns);
				ChangeConfig(&difficulty, &turns);
				break;
			default: // Default error case
				printf("Problem. Default case reached from main menu.");
				printf("Chose: %d. Is not a valid choice", choice);
		}
		
		
	}while(choice != 0);
	
	debug(word, difficulty); 
	
	return 0;
}

int DisplayMenu()
{
	int choice;

	printf("\n\nMain Menu \n");
	printf("1. Play Game\n");
	printf("2. Options\n");
	printf("0. Exit\n");
	
	choice = GetInt("Please select an option: ", 1);
	
	return(choice);
}

void ChangeConfig(int *difficulty, int *turns)
{
	int choice;

	printf("What setting did you want to change?\n");
	printf("0. Nothing\n");
	printf("1. Difficulty\n");
	printf("2. Number of turns\n");
	
	choice = GetInt("Type number: ", 1);
	
	switch(choice)
	{
		case 0:
			break;
		case 1: 
			*difficulty = GetInt("New difficulty value: ", 1);
			break;
		case 2: 
			*turns = GetInt("New turns value: ", 2);
			break;
		default:
			printf("something went wrong. You made a wrong choice");
	}
	
	return;
}
/*
	Performs basic startup functions
		setting random seed
		initializes max turn count variable
		
	More features can be placed here if needed
*/
void Startup(int *difficulty, int *turns)
{
	printf("\n\nWelcome to Hangman!!!!");

	*difficulty = 1;
	*turns = 10;
	srand(time(NULL));
	
	return;
}


/*
	Begins the main loop of the game
	
	Game flow:
		Ask user for a letter
			check letter to see if already used/guessed
		Compare letter to the word 
		Loop until whole word is guessed or out of guesses
*/
void PlayGame(char word[], int turns, int difficulty)
{
	char c;
	char guessed_letters[24] = {'\0'};
	char guessed_word[MAX_SIZE] = {'\0'};
	int length, i, currentturn, count;
	FILE *fp;
	
	
	do
	{
		int valid;
		
		DisplaySettings(difficulty, turns);
		do
		{
			c = GetChar("Are these settings ok? (y/n): ");
			valid = YNCharCheck(c);
		}while(valid == 0);
		
		if(c == 'n')
		{
			ChangeConfig(&difficulty, &turns);
		}
	}
	while(c == 'n');
	
	
	fp = OpenList(difficulty, fp); 
	PickWord(word, fp);
	
	length = strlen(word);
	for(i = 0; i < length; i++)
	{
		guessed_word[i] = '*';
	}

	currentturn = 1;
	// While the word has not been guessed or not out of turns
	while(strcmp(word, guessed_word) || currentturn <= turns)
	{
		char letter;
	
		printf("\Word guessed so far: %s\n", guessed_word);
		printf("\nCurrent turn: %d\n", currentturn);
		printf("Turns to go: %d\n", turns - currentturn);
		//printf("TEST: %s\n", guessed_letters);
		
		// Begin guessing. Letter returned has not been previously guessed
		letter = GuessLetter(guessed_letters);
		
		count = CharacterCount(letter, word, MAX_SIZE);
		if(count > 0)
		{
		
			for(i = 0; i < MAX_SIZE; i++)
			{
				if(word[i] == letter)
				{
					guessed_word[i] = letter;
				}
			}
		}
		else
		{
			//Insert code to update image
			printf("Character not in word!\n\n");
		}
		
		
		
		printf("\n************************\n\n");
		currentturn++;
	}
	printf("Game over\n");
}


/*
	Searches a string for a character and returns the index of that
	characters' first appearance as an integer
	
	if a value of -1 is returned the character could not be found
	in the string
*/
int FindCharIndex(char ch, char *string)
{
	int index = -1;
	char *chIndex;
	
	chIndex = strchr(string, ch);
	
	if(chIndex != NULL)
	{
		index = (int)(chIndex - string);
	}
	
	return(index);
}

/*
	Searches a string or array of chars for a specific character and 
	counts the number of occurences
*/
int CharacterCount(char inChar, const char str[], const int length)
{
	int i, count = 0;
	
	for(i = 0; i < length; i++)
	{
		if(inChar == str[i])
		{
			count++;
		}
	}
	
	return(count);
}

/*
	Displays the current settings that will be used during a game
		difficulty
		turns
	
*/
void DisplaySettings(int difficulty, int turns)
{
	char difficulty_string[7] = {'\0'};

	if(difficulty == 1)
	{
		strncpy(difficulty_string, "easy", 4);
	}
	else if(difficulty == 2)
	{
		strncpy(difficulty_string, "medium", 6);
	}
	else if(difficulty == 3)
	{
		strncpy(difficulty_string, "hard", 4);
	}
	
	printf("\n\nCurrent settings...\n");
	printf("Difficulty is set to: %s\n", difficulty_string);
	printf("The amount of turns to guess the word is set to: %d \n\n", turns);
	
	return;
}

/* 
	Gets a character from the user
	 TODO: do error/validity checking on user input
	 
	 
	 THIS FUNCTION NEEDS MORE WORK. it sucks
*/
char GuessLetter(char guessed_letters[])
{
	char letter;
	int i, length, valid; // Flag to show whether the character has been picked already
	
	length = strlen(guessed_letters);
	
	
	if(length > 0)
	{
		printf("Letters guessed so far:  ");
		for(i = 0; i < length - 1; i++)
		{
			printf("%c, ", guessed_letters[i]);
		}
		printf("%c", guessed_letters[length - 1]);
	}
	
	do
	{
		printf("\nPlease guess a letter: ");
		letter = getchar();
		getchar();
		// TODO: implement input validity checking
		
		
		if(CharacterCount(letter, guessed_letters, 24) > 0)
		{
			printf("Already guessed");
			valid = 1;
		}
		else
		{
			valid = 0;
			
			guessed_letters[length] = letter;
		}
		
	}while(valid == 1);
	
	
	return(letter);
}

/*
	Provides variable output for debugging purposes
*/
void debug(char word[], int difficulty)
{
	printf("\n\nDEBUG FUNCTION, testing variable values\n");
	
	printf("word: %s \nword size: %d\n", word, MAX_SIZE);
	printf("Difficulty: %d", difficulty);
	
	return;
}

/*
	Opens a list of words and points it to FP
	The file is not closed but it is assumed that the file will be 
	closed when used by pickWord().
	
	It is assumed that the difficulty is 1, 2 or 3
*/
FILE *OpenList(int difficulty, FILE *fp)
{
	// Assuming that difficulty is 1, 2 or 3
	if(difficulty == 1)
	{
		fp = fopen("C:/progs/Hangman/words/easy.txt", "r");
	}
	else if(difficulty == 2)
	{
		fp = fopen("C:/progs/Hangman/words/medium.txt", "r");
	}
	else
	{
		fp = fopen("C:/progs/Hangman/words/hard.txt", "r");
	}
	
	return fp;
}

// Gets the difficulty as an integer
// Difficulty should be 1, 2 or 3
int GetDifficulty()
{
	int diff;
	
	diff = GetInt("Please select difficulty: ", 1);
	
	// Test to ensure diff is within correct range before passing to main
	while(diff < 1 || diff > 3)
	{
		diff = GetInt("Try again: ", 1);
	}
	
	return (diff);
}

/*
	Randomly picks a word from a list and stores it in the word array
*/
void PickWord(char word[], FILE *fp)
{
	// variable declarations
	int r, linecount, lines = 0;
	
	// Count lines in file
	while(!feof(fp))
	{
		if(fgetc(fp) == '\n')
		{
			lines++;
		}
	} 
	
	// Return fp to start of file
	rewind(fp);
	
	//printf("\n\nNumber of lines in file: %d\n", lines);
	r = rand() % (lines + 1);
	//printf("Random number: %d\n", r);
	
	
	linecount = 1;
	if(fp != NULL)
	{
		while(fgets(word, MAX_SIZE, fp) != NULL)
		{
			if(linecount == r)
			{
				fclose(fp);
				return;
			}
			linecount++;
		}
	}
	else
	{
		printf("NULL");
	}
	
	printf("Problem");
	fclose(fp);
	return;
} 





