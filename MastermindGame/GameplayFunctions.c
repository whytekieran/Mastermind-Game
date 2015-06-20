//including header file
#include "Mastermind.h"

int userChoices[4];
int compChoices[4];
int loseCnt;
int winCnt;
int gameCnt;
int guessAmnt;
int lose;
bool gameResult;

struct fileStructure
{
	int wins;
	int losses;
	int highScore;
	int gameCounter;
	int guessAmnt;
};//end fileStructure

//mainGameplay calls all the fuctions below it
void mainGameplay(int choice)
{
	//Setting all variables and my arrays to zero for new game
	int i;
	int iChoice;
	gameResult = 0;
	gameCnt = 0;
	loseCnt = 0;
	winCnt = 0;
	guessAmnt = 0;
	lose = 0;
	
	for(i = 0; i < 4; ++i)
	{
		userChoices[i] = 0;
		compChoices[i] = 0;
	}
	
	//Readfile and output the current wins, losses and highscore
	openAndReadFile();

	//Ask the user for how many guesses they would like
	guessAmnt = selectGuessAmount();

	//Generate random colours no repeats our blanks
	generateRandomColours(choice);

	//Show the selection options and brief rules description(easy)
	selectionMenu(choice);
		
	//While result is equal to false or unless maximum tries is reached, keep looping
	while(gameResult == 0)
	{
		++gameCnt;

		if(gameCnt > 1)
		{
			printf("\n  1-RED");
			printf("\n  2-ORANGE");
			printf("\n  3-YELLOW");
			printf("\n  4-GREEN");
			printf("\n  5-BLUE");
			printf("\n  6-INDIGO");
			printf("\n  7-VIOLET\n");
		}

		//Ask the user for their colour choice
		getUserChoices(choice);
			
		//Output the colours they have choosen
		selectedColoursOutput();

		//Compare the choosen colours with the ones randomly generated. Returns true(1) if all right. Otherwise returns (0)
		gameResult = compareColours();

		if(gameCnt == guessAmnt && gameResult != 1)
		{ 
			printf("\n\n\n                     You have reached your maximum tries - Game over");
			printf("\n			                  You Lose                    ");
			++loseCnt;
			lose = 1;
			break;
		}
	}//end while

	//opens the file, compares its stored values with the current games.
	//Writes any changes back into the file
	openReadCompareWriteFile();

	//Asks user if they would like another game, returns either zero or one
	iChoice = playAgain();

	//Depending on the choice made
	if(iChoice == 1)
	{
		//Ask user what difficulty he/she wants and start again
		selectDifficultyAndStart();
	}
	else //or
	{
		//close the program
		exit(EXIT_SUCCESS);
	}
}//end mainGameplay()

//Asks the user to select how many guesses they want
int selectGuessAmount()
{
	int guessAmnt;
	
	do
	{
		printf("\nHow many guesses would you like(Min-5 Max-15): ");
		fflush(stdin);
		scanf_s("%d", &guessAmnt);

		if(guessAmnt < 5 || guessAmnt > 15)
		{
			printf("\nIncorrect, enter a guess amount between 1-15");
		}
		else
		{
			break;
		}
	}
	while(1);

	return (guessAmnt);
}

//Outputs the users choices
void selectedColoursOutput(int choice)
{
	int i;

	printf("\n\nYou have selected:");

	//Copy this section, change userChoices array to compChoices and place it under the generateRandomColours() function
	//inside the mainGameplay function to see what the computer is generating, helps for testing. :)
	for(i = 0; i < 4; ++i)
	{
		switch(userChoices[i])
		{
			case 1:
				printf("\nRed");
				break;
			case 2:
				printf("\nOrange");
				break;
			case 3:
				printf("\nYellow");
				break;
			case 4:
				printf("\nGreen");
				break;
			case 5:
				printf("\nBlue");
				break;
			case 6:
				printf("\nIndigo");
				break;
			case 7:
				printf("\nViolet");
				break;
			case 8:
				printf("\nBlank");
				break;
		}//end switch
	}//end for loop
	//Dont copy past here
}//end selectedColoursOutput()

//Gets the users choices
void getUserChoices(int choice)
{
	int i;

	if(choice == 1 || choice == 2)
	{
		for(i = 0; i < 4; ++i)
		{
			do
			{
				printf("\nEnter number for colour %d: ", (i+1));
				scanf_s("%d", &userChoices[i]);
				fflush(stdin);

				if((userChoices[i] < 1) || (userChoices[i] > 7))
				{
					printf("\n\nYour have entered incorrect information");
					printf("\nEnter a number between from 1-7 for colour selection\n");
				}
			}
			while((userChoices[i] < 1) || (userChoices[i] > 7));
		}//end for loop
	}
	else if(choice == 3)
	{
		for(i = 0; i < 4; ++i)
		{
			do
			{
				printf("\nEnter number for colour or blank %d: ", (i+1));
				scanf_s("%d", &userChoices[i]);
				fflush(stdin);

				if((userChoices[i] < 1) || (userChoices[i] > 8))
				{
					printf("\n\nYour have entered incorrect information");
					printf("\nEnter a number between from 1-8 for colour or blank selection\n");
				}
			}
			while((userChoices[i] < 1) || (userChoices[i] > 8));
		}//end for loop
	}
}

//Compares the colour choice of the user with computer(randomly generated)
bool compareColours()
{
	int i;
	int j;
	int whiteCnt = 0;
	int blackCnt = 0;
	int tempLoopNum = -1;

	//The peg(colour) answer can either be wrong, black or white, It cant be both. 
	//Using a nested for loop to check each user number against all four computer numbers
	//If white is found first only count it once (even if its found more than once) 
	//then if black is found after on same peg, cancel the previous white count, add a black and end the loop
	//If black found first, add the black count then end the loop(move to the next colour and begin checking that)
    
	for(i = 0; i < 4; ++i)
	{
		for(j = 0; j < 4; ++j)
		{
			if(userChoices[i] == compChoices[j])
			{
				if(i != j)
				{
					if(i != tempLoopNum)
					{
						tempLoopNum = i;
						++whiteCnt;
					}
					else
					{
						continue;
					}
				}
				
				if(i == j)
				{
					if(i == tempLoopNum)
					{
						++blackCnt;
						j = 4;
						whiteCnt -= 1;
					}
					else
					{
						++blackCnt;
						j = 4;
					}
				}
			}
		}//end inner for loop
	
	}//end outter for loop

	printf("\n\nYou have %d Black peg(s) and %d White peg(s)\n", blackCnt, whiteCnt);

	if(blackCnt == 4)
	{
		++winCnt;
		printf("\n\nCongratulations you win");
		return (1);
	}	
	else
	{
		return (0);
	}
}//end compareColours()

//Outputs the correct selection menu
void selectionMenu(int choice)
{
	if(choice == 1)
	{
		printf("\n\nEasy Mood (No repeats, No blanks)");
		printf("\n======================================");
		
		printf("\nSelect four Colours");
		printf("\nPlease enter the number of the colour your choosing:\n");
		printf("\n  1-RED");
		printf("\n  2-ORANGE");
		printf("\n  3-YELLOW");
		printf("\n  4-GREEN");
		printf("\n  5-BLUE");
		printf("\n  6-INDIGO");
		printf("\n  7-VIOLET\n");
	}
	else if(choice == 2)
	{
		printf("\n\nMedium Mood (Repeats, No blanks)");
		printf("\n======================================");

		printf("\nSelect four Colours");
		printf("\nPlease enter the number of the colour your choosing:\n");
		printf("\n  1-RED");
		printf("\n  2-ORANGE");
		printf("\n  3-YELLOW");
		printf("\n  4-GREEN");
		printf("\n  5-BLUE");
		printf("\n  6-INDIGO");
		printf("\n  7-VIOLET\n");
	}
	else if(choice == 3)
	{
		printf("\n\nHard Mood (Repeats, blanks allowed)");
		printf("\n============================================");

		printf("\nSelect four Colours or Blank option");
		printf("\nPlease enter the number of the colour or blank your choosing:\n");
		printf("\n  1-RED");
		printf("\n  2-ORANGE");
		printf("\n  3-YELLOW");
		printf("\n  4-GREEN");
		printf("\n  5-BLUE");
		printf("\n  6-INDIGO");
		printf("\n  7-VIOLET");
		printf("\n  8-BLANK\n");
	}
}//end selectionMenu()

//asks the user if they want to play agian
int playAgain()
{
	int iChoice;
	
	do
	{
		printf("\n\n\n\n			            Want to play again?");
		printf("\n                                  =======================");
		printf("\n				 Please enter 1-Yes or 2-No:   ");
		scanf_s("%d", &iChoice);
		fflush(stdin);

		if((iChoice != 1) && (iChoice != 2))
		{
			printf("\n");
			printf("\n                                 Your input is incorrect.");
			printf("\n                           Please enter number 1(Yes) or 2(No)");
			printf("\n");
		}
	}
	while((iChoice != 1) && (iChoice != 2));
	
	return (iChoice);
}

//generates the random colours with/without repeats and with/without blanks 
//depending on users difficulty choice
void generateRandomColours(int choice)
{
	int i;
	time_t t;
	int iRandomNumber;

	//Intializes random number generator
    srand((unsigned) time(&t));
	
	if(choice == 1)
	{
		for(i = 0; i < 4; ++i)
		{
			//Generates random number from 1-7 (7Colours in the game)
			iRandomNumber = (rand() % 7) +1;
			compChoices[i] = iRandomNumber;

			//The following structure of if/else if's are preventing repeats
			if(i > 0 && i < 2)
			{
				if(compChoices[i] == compChoices[i - 1])
				{
					do
					{
						iRandomNumber = (rand() % 7) +1;
						compChoices[i] = iRandomNumber;
					}
					while(compChoices[i] == compChoices[i - 1]);
				}
			}
			else if(i > 1 && i < 3)
			{
				if((compChoices[i] == compChoices[i - 1]) || (compChoices[i] == compChoices[i - 2]))
				{
					do
					{
						iRandomNumber = (rand() % 7) +1;
						compChoices[i] = iRandomNumber;
					}
					while((compChoices[i] == compChoices[i - 1]) || (compChoices[i] == compChoices[i - 2]));
				}
			}
			else if(i > 2 && i < 4)
			{
				if((compChoices[i] == compChoices[i - 1]) || (compChoices[i] == compChoices[i - 2])
					|| (compChoices[i] == compChoices[i - 3]))
				{
					do
					{
						iRandomNumber = (rand() % 7) +1;
						compChoices[i] = iRandomNumber;
					}
					while((compChoices[i] == compChoices[i - 1]) || (compChoices[i] == compChoices[i - 2])
						|| (compChoices[i] == compChoices[i - 3]));
				}	
			}
		}//end for loop

		printf("\n\nFour random Colours Generated - Goodluck");
		printf("\n============================================");
	}
	else if(choice == 2)
	{
		for(i = 0; i < 4; ++i)
		{
			//Generates random number from 1-7 (7 possible Colours in the game)
			iRandomNumber = (rand() % 7) +1;
			compChoices[i] = iRandomNumber;
		}

		printf("\n\nFour random Colours Generated - Goodluck");
		printf("\n============================================");
	}
	else if(choice == 3)
	{
		for(i = 0; i < 4; ++i)
		{
			//Generates random number from 1-8 (7 possible Colours and a Blank in the game)
			iRandomNumber = (rand() % 8) +1;
			compChoices[i] = iRandomNumber;
		}

		printf("\n\nFour random Colours Generated - Goodluck");
		printf("\n============================================");
	}
}//end generateRandomColours

void openAndReadFile()
{
	FILE * fr;                     // declare pointer to a file
	fr = fopen(FILE_NAME, "r");    //open file
	
	if (fr == NULL)//check if the file exists
	{
		printf("\n                                  There was no file to open");
		printf("\n                                      New File Created");
		resetScore();
		main();
	}
	else
	{
		struct fileStructure reader;

		while(fscanf(fr,"%d %d %d %d %d",&reader.wins ,&reader.losses ,&reader.highScore, &reader.gameCounter, &reader.guessAmnt) != EOF)
		{
			printf("\nWins: %d Losses: %d Highscore(LeastGuesses): %d",reader.wins ,reader.losses ,reader.highScore);
			printf("\nHighscore Round Statistics - Guesses Used: %d Guesses Choosen: %d\n",reader.gameCounter ,reader.guessAmnt);
		}
	}
	fclose(fr);
}//end openAndReadFile()

void resetScore()
{
	FILE * fw;                     
	fw = fopen(FILE_NAME, "w");  

	if (fw == NULL)
	{
		printf("\t\tFile could not be opened");
	}
	else
	{
       struct fileStructure writer;
	
	   writer.wins = 0;
	   writer.losses = 0;
	   writer.highScore = 15;
	   writer.gameCounter = 0;
	   writer.guessAmnt = 0;

	   fprintf(fw, "%d %d %d %d %d", writer.wins, writer.losses, writer.highScore, writer.gameCounter, writer.guessAmnt);

	}//end if/else

	fclose(fw);

	printf("\n				   Scores have been reset\n");

	main();
}//end resetScore()

void openReadCompareWriteFile()
{
	int totalWins = 0;
	int totalLosses = 0;
	
	FILE * fr;						//declare pointer for read to file
	FILE * fw;						//declare file pointer for write to file
	fr = fopen(FILE_NAME, "r");     //open file
	
	if (fr == NULL)                 //check if the file exists
	{
		printf("\t\tFile could not be opened");
	}
	else
	{
       struct fileStructure reader;

	   while(fscanf(fr,"%d %d %d %d %d",&reader.wins ,&reader.losses ,&reader.highScore ,&reader.gameCounter, &reader.guessAmnt) != EOF)
	   {
			totalWins = (reader.wins + winCnt);
			totalLosses = (reader.losses + loseCnt);

			if(reader.highScore > gameCnt && lose != 1)
			{
				printf("\nNew HighScore(Least Guesses Used) %d", gameCnt); 
				printf("\nGuesses Choosen: %d Guesses Used: %d", guessAmnt, gameCnt);
			}
	   }

	  fclose(fr);

	  fw = fopen(FILE_NAME, "w");

		if (fw == NULL)       
		{
			printf("\t\tFile could not be opened");
		}
		else
		{
			struct fileStructure writer;

		    writer.wins = totalWins;
		    writer.losses = totalLosses;
			
			if(reader.highScore > gameCnt && lose != 1)
			{
				writer.highScore = gameCnt;
				writer.guessAmnt = guessAmnt;
				writer.gameCounter = gameCnt;
				
			}
			else
			{
				writer.highScore = reader.highScore;
				writer.guessAmnt = reader.guessAmnt;
				writer.gameCounter = reader.gameCounter;
			}
		
		   fprintf(fw, "%d %d %d %d %d", writer.wins, writer.losses, writer.highScore, writer.gameCounter, writer.guessAmnt);
		}//end if/else

		fclose(fw);

	}//end if/else if

}//end openReadCompareWriteFile()

//The commented functions below can allow this game to use a binary file instead of a text file for storage.
//Uncomment and change the file type of Scores.txt to .file (inside Mastermind.h)
//Then comment the current functions openReadCompareWriteFile() resetScore() and openAndReadFile() 
//which are reading and writing a text file
/*void openAndReadFile()
{
	FILE * fr;                     // declare pointer to a file
	fr = fopen(FILE_NAME, "r");    //open file

	if (fr == NULL)//check if the file exists
	{
		printf("\n                                  There was no file to open");
		printf("\n                                      New File Created");
		resetScore();
		main();
	}
	else
	{
        struct fileStructure reader;
		int r;
		
		while((r = fread(&reader, sizeof(struct fileStructure), 1, fr)))
		{
			printf("\nWins: %d, Losses: %d, Highscore(LeastGuesses): %d Guesses Used: %d Guesses Choosen: %d", 
				reader.wins, reader.losses, reader.highScore, reader.gameCounter, reader.guessAmnt);
		}

	}//end if/else

	fclose(fr);
}
void openReadCompareWriteFile()
{
	int totalWins = 0;
	int totalLosses = 0;
	
	FILE * fr;						//declare pointer for read to file
	FILE * fw;						//declare file pointer for write to file
	fr = fopen(FILE_NAME, "r");     //open file
	
	if (fr == NULL)                 //check if the file exists
	{
		printf("\t\tFile could not be opened");
	}
	else
	{
        struct fileStructure reader;
		int r;
		
		while((r = fread(&reader, sizeof(struct fileStructure), 1, fr)))
		{
			totalWins = (reader.wins + winCnt);
			totalLosses = (reader.losses + loseCnt);
			
			if(reader.highScore > gameCnt && lose != 1)
			{
				printf("\nNew HighScore(Least Guesses Used) %d", gameCnt); 
				printf("\nGuesses Choosen: %d Guesses Used: %d", guessAmnt, gameCnt);
			}
		}

		fclose(fr);

		fw = fopen(FILE_NAME, "w");

		if (fw == NULL)       
		{
			printf("\t\tFile could not be opened");
		}
		else
		{
			struct fileStructure writer;

		    writer.wins = totalWins;
		    writer.losses = totalLosses;
			
			if(reader.highScore > gameCnt && lose != 1)
			{
				writer.highScore = gameCnt;
				writer.guessAmnt = guessAmnt;
				writer.gameCounter = gameCnt;
			}
			else
			{
				writer.highScore = reader.highScore;
				writer.guessAmnt = reader.guessAmnt;
				writer.gameCounter = reader.gameCounter;
			}
		
		    fwrite(&writer, sizeof(struct fileStructure), 1, fw);
		}//end if/else

		fclose(fw);

	}//end if/else
}//openReadCompareWriteFile()

void resetScore()
{
	FILE * fw;                     
	fw = fopen(FILE_NAME, "w");    

	if (fw == NULL)
	{
		printf("\t\tFile could not be opened");
	}
	else
	{
       struct fileStructure writer;

	   writer.wins = 0;
	   writer.losses = 0;
	   writer.highScore = 15;
	   writer.gameCounter = 0;
	   writer.guessAmnt = 0;
		
	   fwrite(&writer, sizeof(struct fileStructure), 1, fw);
	}//end if/else

	fclose(fw);

	printf("\n				  Scores have been reset\n");

	main();
}//end reset score*/


