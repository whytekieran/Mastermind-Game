//including header file
#include "Mastermind.h"

int startMenuChoice()
{
	int iChoice;
	
	do
	{
		printf("\n                                     ===================");
		printf("\n                                       MASTERMIND GAME");
		printf("\n                                     ===================");
		printf("\n                                   Would you like to play?");
		printf("\n                          Enter Number 1-Yes, 2-No or 3-Reset Scores  ");
		scanf_s("%d", &iChoice);
		fflush(stdin);
		
		if((iChoice != 1) && (iChoice != 2) && (iChoice != 3))
		{
			printf("\n");
            printf("\n                                 Your input is incorrect.");
			printf("\n                     Please enter number 1(Yes) or 2(No) 3(Reset Scores)");
			printf("\n");
		}
	}
	while((iChoice != 1) && (iChoice != 2) && (iChoice != 3));

	return (iChoice);

}//end startMenuChoice()

int difficultyMenuChoice()
{
	int iChoice;
	
	do
	{
		printf("\n                                 Which difficulty setting would you like?  ");
		printf("\n                                 1 for Easy:  ");
		printf("\n                                 2 for Medium:  ");
		printf("\n                                 3 for Hard:  ");
		printf("\n                                 Enter Number:  ");
		scanf_s("%d", &iChoice);
		fflush(stdin);
		
		if((iChoice != 1) && (iChoice != 2) && (iChoice != 3))
		{
			printf("\n");
            printf("\n                                 Your input is incorrect.");
			printf("\n                     Please enter number 1(Easy), 2(Medium) or 3(Hard)");
			printf("\n");
		}
	}
	while((iChoice != 1) && (iChoice != 2) && (iChoice != 3));

	return (iChoice);
}//end difficultyMenuChoice()

void selectDifficultyAndStart()
{
	int iDifficultyChoice;

	//Ask the user what difficulty he/she wants
	iDifficultyChoice = difficultyMenuChoice();

	//Switch the users choice of difficulty
	switch(iDifficultyChoice)
	{
		//Differant ways of gaming depending on difficulty.
		case 1:
			//Easy mode
			mainGameplay(iDifficultyChoice);
			break;
		case 2:
			//Medium mode
			mainGameplay(iDifficultyChoice);
			break;
		case 3:
			//Hard mode
			mainGameplay(iDifficultyChoice);
			break;
	}//end switch
}//end selectDifficultyAndStart()
