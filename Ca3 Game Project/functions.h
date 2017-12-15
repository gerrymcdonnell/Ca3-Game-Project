#include <string>
#include <vector>
#include <iostream>
#include "object.h"
using namespace std;

extern void StringSplit(string str, string delim, vector<string>& results);
extern int GetIntVal(string strConvert);
extern string GetStringIntVal(int n);
extern void printStringVector(vector <string> s);
extern void printString(string s);
extern bool searchVectorForString(vector <string> v,string s);

//search the game engine loaded objects for an object s
extern int searchVectorForObject(vector <Object> v,string s);
extern string strip_ws(const string& orig);
extern int askUserForInt(string sMsg);
extern int irandomNumber(int n);
extern int getRandomNumberinRange(int min,int max);
//Generic print vector function
template <class T>
extern void printVector(vector <T> myVector);




