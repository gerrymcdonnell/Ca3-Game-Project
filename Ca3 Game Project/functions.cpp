#include <string>
#include <vector>
#include <iostream>
#include "functions.h"
using namespace std;

void StringSplit(string str, string delim, vector<string>& results)
{
int cutAt;
	while((cutAt = str.find_first_of(delim)) != str.npos)
	{
		if(cutAt > 0)	
		{
			results.push_back(str.substr(0,cutAt));
		}
		str = str.substr(cutAt+1);
	}
	if(str.length() > 0)
	{
		results.push_back(str);
	}
}



int GetIntVal(string strConvert) {
  int intReturn;

  // NOTE: You should probably do some checks to ensure that
  // this string contains only numbers. If the string is not
  // a valid integer, zero will be returned.
  intReturn = atoi(strConvert.c_str());

  return(intReturn);
}

string GetStringIntVal(int n)
{
	char buf[5];
	// convert 123 to string [buf]
	itoa(n, buf, 10);
	return buf;
}

void printStringVector(vector <string> s)
{
	for(int x=0;x<s.size();x++)
	{
		cout << "Vector: " <<"[" << x << "] " <<s[x] << endl;
	}
}

void printString(string s)
{
	cout << s <<endl;
}


//search a string vector for a string s
bool searchVectorForString(vector <string> v,string s)
{
	for(int x=0;x<v.size();x++)
	{
		string stmp="";
		stmp=v[x];
		if(stmp.compare(s)==0)
			return true;
	}
	return false;
}


//search the game engine
int searchVectorForObject(vector <Object> v,string s)
{
string objName="";
	
	//cout << "v.size =" << v.size() << endl;

	for(int x=0;x<v.size();x++)
	{
		objName=v[x].getName();	
		if(objName.compare(s)==0)
			return x;
	}
	return -1;
}


//remove the whitepace problem
string strip_ws(const string& orig)
{
	size_t begin = orig.find_first_not_of(" \t");
	size_t end = orig.find_last_not_of(" \t");

	return orig.substr(begin, (end-begin)+1);
}


int askUserForInt(string sMsg)
{
	int n;
	string garbage;

	cout << sMsg;
	cin >> n;
	cin.get();
	

	return n;
}

int irandomNumber(int n)
{
	
	int num = rand()% n + 0;
	return num;

}

int getRandomNumberinRange(int min,int max)
{
	int randomNumber= rand(); // generate random number
	return (randomNumber% max) + min; // get a number between 1 and 6
}

//print a any type of vector
template <class T>
void printVector(vector <T> myVector)
{
	for(int x=0;x<myVector.size();x++)
	{
		cout << "Vector [" <<  x << "] = " <<  myVector[x] <<endl;
	}
}