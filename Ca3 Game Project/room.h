#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include "object.h"
using namespace std;

class Room
{
public:
	Room();
	Room(int iNum,const string& sName,const string& sDesc,vector<int>& sExit,vector<Object>& sObjVector);

	//methods

	//getters
	string getName();//room  name
	string getDesc();//room desc
	int getNum();    //room number

	int getNumberofExits();//how many exists a room has
	bool bIsValidExit(int n); //vector<int> iRoomExits;

	//add an object to a room
	void addObject(Object o);
	int getNumRoomObjects();
	int searchRoomForObject(string s);
	Object getRoomObject(int i);


	//setters
	void setName(string sName);
	void setDesc(string sDesc);
	void setNum(int n);

	void displayRoom();


	//fileIO
	void save(ofstream& outFile);
	void load(ifstream& inFile);





private:
	//data mems
	int iRoomNum;
	string sRoomName;
	string sRoomDesc;
	//vector of room exits
	vector<int> iRoomExits;
	//vector of room objects
	vector <Object> RoomObjects;
	




};
#endif