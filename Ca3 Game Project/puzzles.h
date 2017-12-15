#ifndef PUZZLES_H
#define PUZZLES_H

#include <string>
#include <vector>
#include "functions.h"

using namespace std;

class Puzzles
{
public:
	Puzzles();
	//word games
	void GuesstheBlankWord();
	void GuesstheScrambledWord();
	void SolveThePhrase();
	//number games
	void SolveTheMathsProblem();
	void GuessTheLockCombination();

	
private:
	void readFiletoStringVector(string sFile,vector <string> &sVWords);
	//Generic print vector function
	template <class T>
	void printVector(vector <T> myVector);
	int getRandomNumber(int n);
	void iUniqueSetofRandomNumber(int n,vector <int> &vVectorofNumbers);
	bool searchVectorForNum(vector <int> v,int n);

	//puzzle fucntions
	//***********************************************************************************
	string sScrambleWord(string sWord); //scramble a word
	string sBlankWordOut(string sWord,int iNumBlanks);	//blank out random letters in a word
	//***********************************************************************************
	
	//vectors
	vector <string> sWords;
	vector <string> sLockCombinations;
	vector <string> sWordPhrases;
	vector <int> VectorofNumbers;

	char cAskUserForChar(string sMsg);
	bool isLetterinWord(string sWord,char c);
	bool bGuessTheWord(string sGuessWord,string sTheWord);
	string sAskUserForString(string sMsg);
	int iAskUserForNumber(string sMsg);
	int GetIntVal(string strConvert);
	string GetStringIntVal(int n);

	string getBlankWord(string sWord);

	//mini games
	void GuessTheWord(string sWordToGuess,string sWordtoDisplayToUser);

	string WORD_FILE;
	string WORD_PHRASES_FILE;
	string COMBINATIONLOCK_FILE;

	string sBlankWordAtPos(string sWord,int n);



};
#endif