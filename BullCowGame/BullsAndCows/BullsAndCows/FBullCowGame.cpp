#include "FBullCowGame.h"
#include <map>
#include <time.h>
#define TMap std::map

using int32 = int;
void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = {};
	HIDDEN_WORD = MyRandomHiddenWord;

	MyHiddenWord = HIDDEN_WORD;
	MyMaxTries = MAX_TRIES;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}

FString FBullCowGame::GetRandomHiddenWord()
{
	
	srand(time(NULL));
	
	if (CurrentLevel == 1)
	{
		MyRandomHiddenWord = LevelOneWords[rand() % 10];
	}
	else if (CurrentLevel == 2) 
	{
		MyRandomHiddenWord = LevelTwoWords[rand() % 10];
	}
	else if (CurrentLevel == 3)
	{
		MyRandomHiddenWord = LevelThreeWords[rand() % 10];
	}
	else if (CurrentLevel == 4)
	{
		MyRandomHiddenWord = LevelFourWords[rand() % 10];
	}
	else
	{
		MyRandomHiddenWord = LevelFiveWords[rand() % 10];
	}

		MyHiddenWord = MyRandomHiddenWord;

	//pull form level 
		//run srand
		//pick random word out of apporpiate list
		//return the word as the hidden word
	return MyRandomHiddenWord;
}

FString FBullCowGame::RevelAnswer()
{
	MyRandomHiddenWordRevel = MyRandomHiddenWord;
	return MyRandomHiddenWordRevel;
}



int32 FBullCowGame::IncrementLevel()
{
	CurrentLevel++;

	return int32();
}

int32 FBullCowGame::GetCurrentLevel() const
{
	return CurrentLevel;
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap <int32, int32> WordLengthToMaxTries{ {3,5}, {4,7}, {5,10}, {6,15},{7,25} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

EWordStatus FBullCowGame::IsGuessValid(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EWordStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) 
	{
		return EWordStatus::Not_Lowercase;
	}
	else if(Guess.length() != GetHiddenWordLength())
	{
		return EWordStatus::Wrong_Length;
	}
	else
	{
		return EWordStatus::Ok;
	}
}

// receives a Vaid Guess, incremits turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	//loop through all letters in the guess
	int32 WordLength = MyHiddenWord.length();
	for (int32 MHWCahr = 0; MHWCahr < WordLength; MHWCahr++) 
	{
		for (int32 GChar = 0; GChar < WordLength; GChar++) 
		{
			if (Guess[GChar] == MyHiddenWord[MHWCahr]) 
			{
				if (MHWCahr == GChar) 
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}

	}
	if (BullCowCount.Bulls == WordLength) 
	{
		bGameIsWon = true;
	}
	else 
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

FString FBullCowGame::GetHint(FString Word)
{
	if (CurrentLevel == 1) 
	{
	Hint = Word[rand() % 3];
	}
	else if (CurrentLevel == 2) 
	{
		Hint = Word[rand() % 4];
	}
	else if (CurrentLevel == 3)
	{
		Hint = Word[rand() % 5];
	}
	else if (CurrentLevel == 4)
	{
		Hint = Word[rand() % 6];
	}
	else
	{
		Hint = Word[rand() % 7];
	}

	return Hint;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) 
	{
		return true;
	}

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)//for all letters of the word
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) 
		{ 
			return false; 
		} 
		else
		{
			LetterSeen[Letter] = true;
			//return true;
		}

	}
	return true;
}


bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter: Word) 
	{
		if (!islower(Letter)) 
		{
			return false;
		}
	}
	return true;
}
