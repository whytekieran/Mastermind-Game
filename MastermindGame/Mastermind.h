#ifndef __MASTERMIND_H__
#define __MASTERMIND_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define FILE_NAME "Scores.txt"

typedef int bool;
#define FALSE 0
#define TRUE 1

//Functions called in Mastermind.c
int startMenuChoice();                             //definition in IntroMenuFunctions.c
void resetScore();						           //definition in GameplayFunctions.c - main() also called from within resetScore();

//Functions called in IntroMenuFunctions.c
int difficultyMenuChoice();                        //definition in IntroMenuFunctions.c
void mainGameplay(int);							   //definition in GameplayFunctions.c

//Functions called in GameplayFunctions.c
void generateRandomColours(int);                   //definition in GameplayFunctions.c
void getUserChoices(int);                          //definition in GameplayFunctions.c
void selectedColoursOutput();                      //definition in GameplayFunctions.c
bool compareColours();                             //definition in GameplayFunctions.c
void selectionMenu(int);                           //definition in GameplayFunctions.c
int playAgain();                                   //definition in GameplayFunctions.c
void main();                                       //definition in Mastermind.c
void openAndReadFile();							   //definition in GameplayFunctions.c
void openReadCompareWriteFile();				   //definition in GameplayFunctions.c	
int selectGuessAmount();						   //definition in GameplayFunctions.c

//Function called in GameplayFunctions.c and Mastermind.c
void selectDifficultyAndStart();				   //definition in IntroMenuFunctions.c

#endif