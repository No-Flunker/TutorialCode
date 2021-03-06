// BullCowGame.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//to make syntax Unreal Friendly
using FText = std::string;
using int32 = int;

//Function prototypes as outside a class
void PrintIntro();
void PlayGame();
void PrintGameSummary();

FText GetValidGuess();
bool AskToPlayAgain();

FBullcowGame BCGame;//instantiate a new game


//The entry point for our application
int32 main()
{
	bool bPlayAgain = false ;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);

	return 0;
}

void PrintIntro()
{
	std::cout << std::endl;
	std::cout << "Welcome to Bulls and Cows,a fun word game.\n";
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " Letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

// Plays a single game to completion
void PlayGame()
{
	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxtries();

	//loop for the number of turns asking for guesses

	while (!BCGame.IsGameWon()&& BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		// sumbit valid guess to the game ,and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ".Cows= " << BullCowCount.Cows << "\n\n";
	}
	//TODO summarise game
	PrintGameSummary();
	return;
}

FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		// get a guess from the player
		int32 Currentry = BCGame.GetCurrentTry();
		std::cout << "Try" << Currentry <<" of "<<BCGame.GetMaxtries();
		std::cout << "  .Enter Your Guess: ";
		std::getline(std::cin, Guess);

		// check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
		std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
		break;
		case EGuessStatus::Not_Isogram:
		std::cout << "Please enter a word witout repeating letters.\n\n";
		break;
		case EGuessStatus::Not_Lowercase:
		std::cout << "Please enter all lowercase letters.\n";
		break;
		default:
		//std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
		//std::cout << "Status=Null .\n ";
		break;
		//return Guess;		
		}
	} 
	while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play agine with the same hidden word (y/n) ";
	FText Response = "";
	getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well Done - YOU WIN!\n";
	}
	else
	{
		std::cout << "Better Luck Next Time!\n";
	}
}