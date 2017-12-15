#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>  // For srand() and rand()
#include <algorithm>

#include "puzzles.h"

using namespace std;

Puzzles::Puzzles()
{
	//set up random number
	//***********************************************************************************
	srand((unsigned)time(NULL));
	//***********************************************************************************
	
	WORD_FILE="words.txt";
	WORD_PHRASES_FILE="wordphrases.txt";
	COMBINATIONLOCK_FILE="combinationlocks.txt";

	//test reading in file to vector
	//***********************************************************************************
	readFiletoStringVector(WORD_FILE,sWords);
	printVector(sWords);
	
	readFiletoStringVector(COMBINATIONLOCK_FILE,sLockCombinations);
	printVector(sLockCombinations);

	//word phrases
	readFiletoStringVector(WORD_PHRASES_FILE,sWordPhrases);
	//printVector(sWordPhrases);
	
	//***********************************************************************************
}

void Puzzles::SolveThePhrase()
{
	int iRandomNumber=0;
	string sThePhrase="";
	string sTheWord="";
	string myGuess="";
	int iLen=sWordPhrases.size();
	int iNumWordsInPhrase=0;
	string sDisplayWordtoUser="";
	vector <string> vResults;

	//get a random word from word vector
	iRandomNumber=getRandomNumber(iLen);

	//get a word from word vector
	sThePhrase=sWordPhrases[iRandomNumber];

	//split the string
	StringSplit(sThePhrase," ",vResults);

	//printVector(vResults);

	//blank out one word
	iRandomNumber=getRandomNumber(iLen);
	sTheWord=vResults[iRandomNumber];

	iNumWordsInPhrase=vResults.size();

	for(int i=0;i<iNumWordsInPhrase;i++)
	{
		if(iRandomNumber!=i)
			sDisplayWordtoUser+=vResults[i] + " "; 
		else
			sDisplayWordtoUser+=getBlankWord(vResults[i] + " ");
	}
	//cout << "Word removed = " << sTheWord << endl;
	cout << "Jumbled phrase =" << sDisplayWordtoUser << endl;

	cout << "'" << sDisplayWordtoUser  <<"'"<< endl;
	myGuess=sAskUserForString("Guess the Missing Word: ");


	while(bGuessTheWord(sTheWord,myGuess)==false)
	{
		cout << "Wrong Answer, Keep Trying." << endl;		
		//blank out the word and display it
		cout << sDisplayWordtoUser << endl;
		//ask user for guess
		myGuess=sAskUserForString("Guess the Missing Word: ");
	}
	cout << "Correct!" << endl;
}


void Puzzles::GuessTheLockCombination()
{
	int iRandomNumber=0;
	//get the size of the word vector
	int iLen=sLockCombinations.size();
	string sLockCombo="";
	string sMissingNumber="";
	string myGuess="";
	string sDisplayWordtoUser="";

	iRandomNumber=getRandomNumber(iLen);
	
	//get a random string from the vector
	sLockCombo=sLockCombinations[iRandomNumber];
	
	//the missing number/string is stored here
	//eg 951
	iLen=sLockCombo.size(); //random number between 0 and 2 i.e 3 chars long string
	iRandomNumber=getRandomNumber(iLen);
	sMissingNumber=sLockCombo[iRandomNumber];


	//blank off one number
	sDisplayWordtoUser=sBlankWordAtPos(sLockCombo,iRandomNumber);

	cout << "Find the Missing Number: " << sDisplayWordtoUser << endl;
	myGuess=sAskUserForString("Guess Correct Code to Proceed: ");

	while(bGuessTheWord(sMissingNumber,myGuess)==false)
	{
		cout << "Find the Missing Number: " << sDisplayWordtoUser << endl;
		myGuess=sAskUserForString("Guess Correct Code to Proceed: ");
	}
	cout << "Correct Code! " << sLockCombo<< endl;

}


void Puzzles::SolveTheMathsProblem()
{
	int n1=0;
	int n2=0;
	int ans=0;
	int userAns=0;
	int imathsOP=0;
	string mathsOperations[] = {"+", "X", "-"};
	string sMathsOp="";
	string sQuestion="";

	imathsOP=getRandomNumber(2);
	sMathsOp=mathsOperations[imathsOP];

	//get two random numbers
	n1=getRandomNumber(99);
	n2=getRandomNumber(99);

	if(sMathsOp=="+")
		ans=n1+n2;
	else if(sMathsOp=="X")
		ans=n1*n2;
	else if (sMathsOp=="-")
		ans=n1-n2;


	sQuestion="What is " + GetStringIntVal(n1) + " " + sMathsOp + " " + GetStringIntVal(n2) + " ? Your Answer: ";
	userAns=iAskUserForNumber(sQuestion);
	while(userAns!=ans)
	{
		cout << "Wrong answer, try again." << endl;
		userAns=iAskUserForNumber(sQuestion);
	}
	cout << "Correct Answer! " << ans << endl;
}


void Puzzles::GuesstheScrambledWord()
{
	int iRandomNumber=0;
	//get the size of the word vector
	int iLen=sWords.size();

	string sDisplayWordtoUser="";

	//get a random word from word vector
	iRandomNumber=getRandomNumber(iLen);

	//get a word from word vector
	string sTheWord=sWords[iRandomNumber];

	//scramble the word
	sDisplayWordtoUser=sScrambleWord(sTheWord);

	//start the game
	GuessTheWord(sTheWord,sDisplayWordtoUser);
}

void Puzzles::GuesstheBlankWord()
{
	int iRandomNumber=0;
	//get the size of the word vector
	int iLen=sWords.size();

	string sDisplayWordtoUser="";

	//get a random word from word vector
	iRandomNumber=getRandomNumber(iLen);

	//get a word from word vector
	string sTheWord=sWords[iRandomNumber];

	//blank out the word and display it
	sDisplayWordtoUser=sBlankWordOut(sTheWord,2);

	//start the game
	GuessTheWord(sTheWord,sDisplayWordtoUser);
}

//mini game functions
void Puzzles::GuessTheWord(string sWordToGuess,string sWordtoDisplayToUser)
{
	string myGuess="";	

	cout << sWordtoDisplayToUser << endl;
	//ask user for guess
	myGuess=sAskUserForString("Guess the Word: ");

	while(bGuessTheWord(sWordToGuess,myGuess)==false)
	{
		cout << "Wrong Answer, Keep Trying." << endl;		
		//blank out the word and display it
		cout << sWordtoDisplayToUser << endl;
		//ask user for guess
		myGuess=sAskUserForString("Guess the Word: ");
	}

	if(bGuessTheWord(sWordToGuess,myGuess)==true)
		cout << "correct" << endl;
}



//reads a file line by line into a string vector
void Puzzles::readFiletoStringVector(string sFile,vector <string> &sVWords)
{
  string line;
  ifstream myfile;
  myfile.open(sFile.c_str());

  while (myfile.good())
  {
      getline (myfile,line);
	  sVWords.push_back(line);
      //cout << line << endl;
  }
  myfile.close();
}


//print a any type of vector
template <class T>
void Puzzles::printVector(vector <T> myVector)
{
	for(int x=0;x<myVector.size();x++)
	{
		cout << "Vector [" <<  x << "] = " <<  myVector[x] <<endl;
	}
}


//scramble a word
string Puzzles::sScrambleWord(string sWord)
{
	//get the size of the word
	int iLen=sWord.size();

	//create a vector to store the random numbers
	vector <int> myVector;
	string sTemp="";

	//generate some random numbers from 0 to len of string
	iUniqueSetofRandomNumber(iLen,myVector);

	for(int x=0;x<iLen;x++)
	{
		//cout << sWord[myVector[x]];
		sTemp+=sWord[myVector[x]] ;
	}	

	return sTemp;
}


//take in a word and put Blanks in it
string Puzzles::sBlankWordOut(string sWord,int iNumBlanks)
{
	//const int TOTAL_BLANKS=2;
	const char BLANK_CHAR='_';

	int iLen=sWord.size();
	string sBlankWord="";
	//create a vector to store the random numbers
	vector <int> myVector;

	if(iLen>0)
	{
		sBlankWord=sWord;
		//generate some random numbers from 0 to len of string
		iUniqueSetofRandomNumber(iLen,myVector);
		//how many to blank out?
		for(int x=0;x<iNumBlanks;x++)
		{
			sBlankWord[myVector[x]]=BLANK_CHAR;
		}
		return sBlankWord;
	}
	else
	{
		return "";
	}
}

string Puzzles::sBlankWordAtPos(string sWord,int n)
{
	int iLen=sWord.size();
	string sTemp=sWord;
	if(iLen>0)
	{
		sTemp[n]='_';
		return sTemp;
	}
}

int Puzzles::getRandomNumber(int n)
{
	int num = rand()% n + 0;
	return num;
}


//generates a unique set of random numbers
void Puzzles::iUniqueSetofRandomNumber(int iMaxNum,vector <int> &vVectorofNumbers)
{
	int randomNum = getRandomNumber(iMaxNum);

	//intialise array
	for(int x=0;x<iMaxNum;x++)
	{
		vVectorofNumbers.push_back(-1);
	}

	//search vector for that random number if its not in the array
	//add it
	for(int z=0;z<iMaxNum;z++)
	{
		randomNum = getRandomNumber(iMaxNum);
		//if the number is in the vector then we need a new number
		while(searchVectorForNum(vVectorofNumbers,randomNum)==true)
		{
			randomNum = getRandomNumber(iMaxNum);//get a new number
		}
		vVectorofNumbers[z]=randomNum;//store number			
	}

	//print result
	//printVector(vVectorofNumbers);

}



//search vector for number n
bool Puzzles::searchVectorForNum(vector <int> v,int n)
{
	for(int x=0;x<v.size();x++)
	{
		if(v[x]==n)
			return true;
	}	
	return false;
}



char Puzzles::cAskUserForChar(string sMsg)
{
	char stemp;
	cout << sMsg;
	cin >> stemp;
	return stemp;	
}


//search a word for a letter if its in return true
bool Puzzles::isLetterinWord(string sWord,char c)
{
	if(sWord.find(c)!= string::npos)
		return true;
	else
		return false;	
}

//just compares 2 words
bool Puzzles::bGuessTheWord(string sGuessWord,string sTheWord)
{
	if(sGuessWord.compare(sTheWord)==0)
		return true;
	else
		return false;
}


string Puzzles::sAskUserForString(string sMsg)
{
	string stemp;
	cout << sMsg;
	getline(cin,stemp); //cin doest work with spaces
	return stemp;
}

int Puzzles::iAskUserForNumber(string sMsg)
{
	int stemp;
	cout << sMsg;
	cin >> stemp;
	return stemp;
	
}

int Puzzles::GetIntVal(string strConvert) 
{
  int intReturn;

  // NOTE: You should probably do some checks to ensure that
  // this string contains only numbers. If the string is not
  // a valid integer, zero will be returned.
  intReturn = atoi(strConvert.c_str());

  return(intReturn);
}

string Puzzles::GetStringIntVal(int n)
{
	char buf[5];
	// convert 123 to string [buf]
	itoa(n, buf, 10);
	return buf;

}




string Puzzles::getBlankWord(string sWord)
{
	string stemp;
	const char BLANK_LETTER='_';
	for(int i=0;i<sWord.size();i++)
	{
		if(sWord[i]==' ')
			stemp=stemp + " ";
		else
			stemp=stemp + BLANK_LETTER;
	}
	//cout << "\n\n\nThe Word is " << stemp << endl;
	return stemp;

}

