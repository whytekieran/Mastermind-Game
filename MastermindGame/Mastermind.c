//including header file
#include "Mastermind.h"

void main()
{
	int iStartChoice;

	iStartChoice = startMenuChoice();

	if(iStartChoice == 1)
	{
		//Move on to difficulty selection
		selectDifficultyAndStart();
	}
	else if(iStartChoice == 2)
	{
		//close the program
		exit(EXIT_SUCCESS);
	}
	else if(iStartChoice == 3)
	{
		//reset all the scores
		resetScore();
	}

	printf("\n");
    system("pause");

}//end main()

