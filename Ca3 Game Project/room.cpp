#include "room.h"
#include "functions.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const string TEXT_SEP="=========================================";


Room::Room()
{
	iRoomNum=0;
	sRoomName="";
	sRoomDesc="";
	
	
}

Room::Room(int iNum,const string& sName,const string& sDesc,vector<int>& sExit,vector<Object>& sObjVector)
{
	iRoomNum=iNum;
	sRoomName=sName;
	sRoomDesc=sDesc;
	//vectors
	iRoomExits=sExit;			//room exit vector
	RoomObjects=sObjVector;		//room object vector
	
}

//getters
string Room::getName()
{
	return sRoomName;
}


string Room::getDesc()
{
	return sRoomDesc;
}

int Room::getNum()
{
	return iRoomNum;
}


int Room::getNumberofExits()
{
	return iRoomExits.size();
}


//setters
void Room::setName(string sName)
{
	sRoomName=sName;
}

void Room::setDesc(string sDesc)
{
	sRoomDesc=sDesc;
}

void Room::setNum(int n)
{
	iRoomNum=n;
}



void Room::displayRoom()
{
	string stmp="";

	cout << TEXT_SEP<< endl;

	//DEBUG Version
	//cout << "Room Num: " << iRoomNum << endl;
	//cout << "Room Name: " << sRoomName << endl;
	//cout << "Room Desc: " << sRoomDesc << endl;


	cout << "Location: ["<< iRoomNum << "] ," << sRoomName << endl;
	cout << sRoomDesc << endl;
	

	//process the room description and objects to the room


	//room objects
	//************************************************************************
	cout << endl;
	cout << "There is " << RoomObjects.size() << " objects in this room:"<<endl;
	

	if(RoomObjects.size()==1)
	{
		cout << "You see a "<< RoomObjects[0].getName() << endl;
	}
	else if(RoomObjects.size()==2)
	{
		cout << "You see a ["<< RoomObjects[0].getName() << "] and a [" << RoomObjects[1].getName() << "] " << endl;
	}
	else
	{
			//build up the string displaying the objects name
			//i.e two objects object1 , object 2
			for(int x=0;(unsigned)x<RoomObjects.size();x++)
			{
				//cout << "x= " << x << "tot objs " << RoomObjects.size() << endl;
				if(x==RoomObjects.size()-1)
				{
					//you see obj , obj					
					stmp+= " and a [" + RoomObjects[x].getName() + "] .";					
				}
				else
				{
					stmp+= "[" +RoomObjects[x].getName() + "] ,";
				}
			}
			cout << "You see a " << stmp << endl;
	}		
	//************************************************************************



	cout << endl;
	//show room exits
	//only testing so room names wont appear here
	stmp="";
	//************************************************************************
	cout << "There is " << getNumberofExits() << " exit's in this room:"<<endl;

	if(iRoomExits.size()==1)
	{
		cout << "From here you can go Room: [" << iRoomExits[0]<< "]" <<endl;
	}
	else
	{
		for(int x=0;x<iRoomExits.size();x++)
		{
			//GetStringIntVal
			//cout << "exits " << iRoomExits[x] << endl;
			stmp+= "[" + GetStringIntVal(iRoomExits[x]) + "] ";

			//print room names,will need acces to gameengine gamerooms vector
			//printString("Test");
			//printString(getRoomName(x));
		}


		//Note only displays room numbers
		cout << "From here you can go to Rooms: " << stmp<<endl;
		//cout << "test " << GameRooms[iRoomExits[x]]. << endl;
	}

	//************************************************************************

	cout << TEXT_SEP << endl;
}


//unused
void Room::save(ofstream& outFile)
{

	outFile << "RoomNumber= " << iRoomNum << endl;
    outFile << "RoomName= " << sRoomName<< endl;
	outFile << "RoomDesc= " << sRoomDesc << endl;
	//save exits
	//Exits= 6 
    outFile << endl;

}

//problems reading in lines with sapces
void Room::load(ifstream& inFile)
{
    string garbage;
	const int size= 600;
    char data[size];
	int itmp=0;
	vector <string>tmp;
	
	iRoomExits.clear();

    inFile >> garbage >> iRoomNum; //works

	inFile >> garbage; //get rid of the roomname=
	inFile.getline(data, size);
	sRoomName=data;

    inFile >> garbage;//get rid of the roomdesc=
    inFile.getline(data, size);
	sRoomDesc=data;

	//room exits
	inFile >> garbage;//get rid of the roomdesc=

	inFile.getline(data, size);

	//cout << "Room exit string " << data << endl;
	
	StringSplit(data," ",tmp);

	//convert to int
	for(int x=0;(unsigned)x<tmp.size();x++)
	{
		itmp=GetIntVal(tmp[x]);
		iRoomExits.push_back(itmp);
	}
  
}


//room objects
//************************************************************************************
void Room::addObject(Object o)
{
	RoomObjects.push_back(o);
}


Object Room::getRoomObject(int i)
{
	return RoomObjects[i];
}


int Room::getNumRoomObjects()
{	
	return RoomObjects.size();
}

//search the room for an object s and return position in the vector
int Room::searchRoomForObject(string s)
{
	string objName="";
	
	for(int x=0;x<RoomObjects.size();x++)
	{
		objName=RoomObjects[x].getName();
	
		if(objName.compare(s)==0)
			return x;
	}
	return -1;
}

bool Room::bIsValidExit(int n)
{
	for(int x=0;x<iRoomExits.size();x++)
	{
		if(iRoomExits[x]==n)
			return true;
	}
	return false;
}
//************************************************************************************