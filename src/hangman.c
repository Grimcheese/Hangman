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
#include <direct.h>

#include "header/input.h"

#define MAX_SIZE 11


// Function prototypes
void Startup(int*, int*);
int GetDifficulty(void);
char* PickWord(FILE *);
void debug(char[], int);
FILE *OpenList(int);
void PlayGame(int, int);
void DisplayMenu(void);
void DisplaySettings(int, int);
void ChangeConfig(int*, int*);
char GuessLetter(char[]);
int CharacterCount(char, const char[], const int);
char* concat(char*, char*);
char* HideWord(char*);
void RemoveNewLine(char[]);

int main()
{
	int difficulty, turns, choice;

	Startup(&difficulty, &turns);
	
	do
	{
		DisplayMenu();
		choice = GetInt("Please select an option: ");
		
		switch(choice)
		{
			case 0: // Exit game
				printf("Goodbye");
				break;
			case 1: // Begin playing the game
				PlayGame(turns, difficulty);
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
	
	return 0;
}

void DisplayMenu()
{
	printf("\n\nMain Menu \n");
	printf("1. Play Game\n");
	printf("2. Options\n");
	printf("0. Exit\n");
	
	return;
}

void ChangeConfig(int *difficulty, int *turns)
{
	int choice;

	printf("What setting did you want to change?\n");
	printf("0. Nothing\n");
	printf("1. Difficulty\n");
	printf("2. Number of turns\n");
	
	choice = GetInt("Please select an option: ");
	
	switch(choice)
	{
		case 0:
			break;
		case 1: 
			*difficulty = GetInt("New difficulty value: ");
			break;
		case 2: 
			*turns = GetInt("New turns value: ");
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
void PlayGame(int turns, int difficulty)
{
	char guessed_letters[24] = {'\0'};
	
	// This do while loop should be in it's own function to make PlayGame() clearer
	char c;
	do
	{	
		DisplaySettings(difficulty, turns);
	
		int valid = 0;
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
	
	// word and hiddenWord are allocated. NEED TO FREE THEM when finished
	FILE* fp = OpenList(difficulty); 
	char* word = PickWord(fp);
	printf("%s\n", word);
	char* hiddenWord = HideWord(word);

	int currentturn = 1;
	// While the word has not been guessed or not out of turns
	while(strcmp(word, hiddenWord) || currentturn <= turns)
	{
		int length = strlen(word);
		char letter;
	
		printf("\nWord guessed so far: %s\n", hiddenWord);
		printf("\nCurrent turn: %d\n", currentturn);
		printf("Turns to go: %d\n", turns - currentturn);
		//printf("TEST: %s\n", guessed_letters);
		
		// Begin guessing. Letter returned has not been previously guessed
		letter = GuessLetter(guessed_letters);
		
		int count = CharacterCount(letter, word, length);
		if(count > 0)
		{
		
			for(int i = 0; i < length; i++)
			{
				if(word[i] == letter)
				{
					hiddenWord[i] = letter;
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
	
	return;
}

char* HideWord(char* word)
{
	int length = strlen(word) + 1;
	char* hiddenWord = malloc(length);
	for(int i = 0; i < length; i++)
	{
		if(i == length - 1)
		{
			hiddenWord[i] = "\0";
		}
		else
		{
			hiddenWord[i] = "*";
		}
	}
	return(hiddenWord);
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
FILE *OpenList(int difficulty)
{
	
	FILE* fp;
	char* cwd = _getcwd(NULL, 0);
	// Assuming that difficulty is 1, 2 or 3
	if(difficulty == 1)
	{
		char* fileloc = concat(cwd, "/dat/easy.txt");
		fp = fopen(fileloc, "r");
		free(fileloc);
	}
	else if(difficulty == 2)
	{
		char* fileloc = concat(cwd, "/dat/medium.txt");
		fp = fopen(fileloc, "r");
		free(fileloc);
	}
	else
	{
		char* fileloc = concat(cwd, "/dat/hard.txt");
		fp = fopen(fileloc, "r");
		free(fileloc);
	}
	
	free(cwd);
	return fp;
}

char* concat(char* str1, char* str2)
{
	char* result = malloc(strlen(str1) + strlen(str2) + 1);
	
	strcpy(result, str1);
	strcat(result, str2);
	
	return result;
}
// Gets the difficulty as an integer
// Difficulty should be 1, 2 or 3
int GetDifficulty()
{
	int diff;
	
	diff = GetInt("Please select difficulty: ");
	
	// Test to ensure diff is within correct range before passing to main
	while(diff < 1 || diff > 3)
	{
		diff = GetInt("Try again: ");
	}
	
	return (diff);
}

/*
	Randomly picks a word from a list and stores it in the word array
*/
char* PickWord(FILE *fp)
{
	// variable declarations
	int r, linecount, lines = 0, MAX_WORD_SIZE = 20;
	char temp[MAX_WORD_SIZE];
	
	
	// Count lines in file
	while(fgets(temp, MAX_WORD_SIZE, fp))
	{
		lines++;
	} 
	
	// Return fp to start of file
	rewind(fp);
	
	//printf("\n\nNumber of lines in file: %d\n", lines);
	r = rand() % (lines + 1);
	//printf("Random number: %d\n", r);
	
	linecount = 1;
	if(fp != NULL)
	{
		for(int i = 0; i < MAX_WORD_SIZE; i++)
		{
			temp[i] = "\0";
		}
		
		while(fgets(temp, MAX_WORD_SIZE, fp))
		{
			RemoveNewLine(temp);
			printf("%s", temp);
			if(linecount == r)
			{
				int length = strlen(temp);
				char* word = malloc(length + 1);
				strncpy(word, temp, length);
				fclose(fp);
				printf("%s\n", word);
				return(word);
			}
			linecount++;
		}
	}
	else
	{
		printf("File Pointer is NULL");
	}
	
	printf("Problem");
	fclose(fp);
	return(NULL);
} 

void RemoveNewLine(char str[])
{
	int length = strlen(str);
	for(int i = 0; i < length + 1; i++)
	{
		if(str[i] == "\n")
		{
			str[i] = "\0";
		}
	}
	return;
}



