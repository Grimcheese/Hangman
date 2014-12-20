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

#define MAX_SIZE 11


// Function prototypes
void Startup(int*, int*);
int GetDifficulty(void);
void PickWord(char[], FILE *);
void debug(char[], int);
FILE *OpenList(int, FILE *);
void PlayGame(char word[]);
int DisplayMenu(void);

int main()
{
	char word[MAX_SIZE];
	int difficulty, turns;

	Startup(&turns, &difficulty);
	
	do
	{
		choice = DisplayMenu();
		
		switch(choice)
		{
			case 0: // Exit game
				printf("Goodbye");
				break;
			case 1: // Begin playing the game
				PlayGame(word);
				break;
			case 2: // Enter game config
				DisplaySettings(difficulty, turns);
				ChangeConfig();
				break;
			default: // Default error case
				printf("problem. Default case reached from main menu.");
				printf("%Chose: d", choice);
				system.exit();
		}
		
		
	}while(choice == 0);
	
	debug(word, difficulty); 
	
	return 0;
}

void ChangeConfig(int *difficulty, int *turns)
{
	int choice;

	printf("What setting did you want to change?\n");
	printf("1. Difficulty\n");
	printf("2. Number of turns\n");
	
	printf("Type number: ");
	scanf("%d", &choice);
	
	switch(choice)
	{
		case 1: 
			printf("New difficulty value: ");
			scanf("%d", &difficulty);
			break;
		case 2: 
			printf("New turns value: ");
			scanf("%d", &turns);
			break;
		default:
			printf("something went wrong. You made a wrong choice");
	}
}
/*
	Performs basic startup functions
		setting random seed
		initializes max turn count variable
		
	More features can be placed here if needed
*/
void Startup(int *turns, int *difficulty)
{
	difficulty = 1;
	turns = 10;
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
void PlayGame(char word[])
{
	char cont;
	char guessed_letters[24] = {'\0'};
	char guessed_word[MAX_SIZE] = {'\0'};
	int length, i, currentturn, count;
	FILE *fp;
	
	
	DisplaySettings(difficulty, turns);
	
	printf("Are these settings ok?\n");
	printf("Type y/n: ");
	scanf("%c", &cont);
	
	
	if(cont == 'n')
	{
		ChangeConfig(&difficulty, &turns);
	}	
	
	
	fp = OpenList(difficulty, fp); 
	PickWord(word, fp);
	
	length = strlen(word);
	for(i = 0; i < length; i++)
	{
		guessed_word[i] = '*';
	}

	currentturn = 1;
	// While the words are not the same
	while(strcmp(word, guessed_word) != 0)
	{
	
		// Begin guessing. Letter returned has not been previously guessed
		letter = GuessLetter(guessed_letters);
		
		
		count = CharacterCount(letter, word, MAX_SIZE);
		if(count > 0)
		{
			printf("%c appears %d times", letter, count);
			
			for(i = 0; i < count; i++)
			{
				
			}
		}
		else
		{
			//Insert code to update image
			printf("Character not in word!");
		}
		currentturn++;
	}
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
	char difficulty_string[7];

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
	
	printf("Current settings...\n");
	printf("Difficulty is set to %c\n", difficulty_string);
	printf("The amount of turns to guess the word is set to %d\n", turns);
	
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
	int i;
	int valid = 1; // Flag to show whether the character has been picked already
	
	do
	{
		printf("Please guess a letter: ");
		scanf("%c", &letter);

		// TODO: implement input validity checking
		
		
		if(CharacterCount(letter, guessed_letters, 24) > 0)
		{
			valid = 1;
		}
		else
		{
			valid = 0;
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
	int diff = 0;
	
	printf("Please select difficulty: ");
	scanf("%d", &diff);
	
	// Test to ensure diff is within correct range before passing to main
	while(diff < 1 || diff > 3)
	{
		printf("Try again: ");
		scanf("%d", &diff);
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
	
	printf("Number of lines in file: %d\n", lines);
	r = rand() % (lines + 1);
	printf("Random number: %d", r);
	
	
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