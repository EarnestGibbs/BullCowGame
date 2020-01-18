/* This is the console executable, that makes use of the BullCow Class
this acts as the beiw in the mvc pattern, and is responsible for all user interaction.
for game logic see the fbullcow class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"


FBullCowGame BCGame;//Instantiate a new game

using int32 = int32;
using Ftext = std::string;
void PrintIntro();
Ftext GetGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();
void PrintGameInstructions();

int main()
{
	PrintGameInstructions();
	bool bPlayAgain = false;
	do 
	{
		BCGame.GetRandomHiddenWord();
		PrintIntro();
		PlayGame();
		
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);

	return 0;
}


void PrintIntro()
{
	//introducing the game
	std::cout << "\nLevel: " << BCGame.GetCurrentLevel();
	std::cout << "\nCan you guess the: " << BCGame.GetHiddenWordLength() << " letter word that I am thinking of.";
	std::cout << "\nYour hint is: " << BCGame.GetHint(BCGame.RevelAnswer());
	return;
}

Ftext GetGuess()
{
	Ftext Guess = "";
	EWordStatus Status = EWordStatus::Invalid_Status;
	do {
		//Getting a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "\nTry " << CurrentTry << " of "<< BCGame.GetMaxTries() <<". What is your guess: ";
		getline(std::cin, Guess);

		EWordStatus Status = BCGame.IsGuessValid(Guess);
		switch (Status)
		{
		case EWordStatus::Not_Isogram:
			std::cout << "Please enter a word with out repeating letters.\n";
			break;
		case EWordStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EWordStatus::No_Special_Characters:
			std::cout << "Do not enter any Special Characters.\n";
			break;
		case EWordStatus::Not_Lowercase:
			std::cout << "Please enter all lower case letters.\n";
			break;
		default:
			//assume the guess is valid
			return Guess;
			break;
		}
		

		std::cout << std::endl;
	} while (Status != EWordStatus::Ok);//keep looping until we get no errors
	return Guess;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	//loop asking for guesses while the game is not won
	//and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		Ftext Guess = GetGuess();

		//submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;

		//std::cout << "\nYour Guess was: " << Guess;

	}
	PrintGameSummary();
	return;
}

bool AskToPlayAgain() 
{
	std::cout << "Do you want to play agian?\n" << "Yes or No\n";
	Ftext Response = "";
	getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}
void PrintGameInstructions() 
{
	std::cout << "Welcome to Bulls and Cows, a fun word game!\n";
	std::cout << "Guess the word to win the game with your only hints being Bulls and Cows.\n";
	std::cout << "Bulls mean that the letter is in the right place!\n";
	std::cout << "Cows mean that the letter is in the word.\n";
	std::cout << "The words are isograms meaning no repeating letters!\n\n";
	return;
}
void PrintGameSummary() 
{
	if (BCGame.IsGameWon()) 
	{
		std::cout << "\nYou win \n";
		BCGame.IncrementLevel();
	}
	else 
	{
		std::cout << "\nThe word was - " << BCGame.RevelAnswer();
		std::cout << "\nBad luck this time \n";

	}
}

