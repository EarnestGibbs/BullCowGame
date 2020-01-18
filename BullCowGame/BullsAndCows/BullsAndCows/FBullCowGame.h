#pragma once
#include <string>

using int32 = int;
using FString = std::string;

//all values intialised to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;

};

enum class EWordStatus
{
	Invalid_Status,
	Ok,
	Not_Isogram,
	Wrong_Length,
	No_Special_Characters,
	Not_Lowercase
};

class FBullCowGame
{
public:
	FBullCowGame();

	FString GetRandomHiddenWord();
	FString RevelAnswer();
	FString GetHint(FString);
	int32 IncrementLevel();
	int32 GetCurrentLevel() const;
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EWordStatus IsGuessValid(FString) const;

	void Reset(); //todo  Make a more rich return value
	FBullCowCount SubmitValidGuess(FString);

private:

	//See constructor
	
	int32 MyCurrentTry;
	int32 MyMaxTries;
	int32 CurrentLevel = 1;
	FString MyHiddenWord;
	FString MyRandomHiddenWord;
	FString MyRandomHiddenWordRevel;
	FString HIDDEN_WORD;
	FString Hint;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

	FString LevelOneWords[10] = {"ace","and","dig","dog","bat","bra","spy","sew","urn","use"};
	FString LevelTwoWords[10] = {"acid","acne","blam","bail","cake","cafe","darn","dart","each","echo"};
	FString LevelThreeWords[10] = {"above","adopt","baker","baler","candy","cable","daily","debit","elbow","eight"};
	FString LevelFourWords[10] = {"absent","action","bakery","baited","calmed","cavity","danish","deputy","elvish","earing"};
	FString LevelFiveWords[10] = {"abolish","abridge","baptism","balcony","chamber","carbine","darting","darkest","elastic","earlock"};

};

