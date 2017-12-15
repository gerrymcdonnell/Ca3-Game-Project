#include "object.h"
#include "functions.h"

#include <iostream>
using namespace std;

Object::Object()
{
	Name="objectDefault";
	Desc="its just an object";
	bUsedState=false;
}

Object::Object(const string& sName,const string& sDesc)
{
	Name=sName;
	Desc=sDesc;
	bUsedState=false;

}

std::string Object::getDesc()
{
	return Desc;
}

std::string Object::getName()
{
	return Name;
}



void Object::displayObject()
{
	if(Name!="")
	{	cout<<"'DEBUG::DISPLAYING OBJECT()': Its a " << Name << ". " << Desc << endl;
	}
	else
	{	cout << "ERROR: this object has no data."<<endl;
	}
}


string Object::examine()
{
	return string("> You Examine the " + Name + " , " + Desc);
}

string Object::read()
{
	return string("> You read the " + Name + " , " + Desc);
}

string Object::open()
{
	return string("> Nothing happens...");
}


string Object::useWith(Object& object)
{
if(object.bisObjectUsed()==false)
{
	if(object.getName() == "door")
	{
		//object.setOpen(true);
		return "Door is open";
	}
	else
	{
		return "not a door";
	}
}
}


void Object::save(ofstream& outFile)
{
    outFile << "Name= " << Name << endl;
    outFile << "Desc= " << Desc << endl;
    outFile << endl;

}

void Object::load(ifstream& inFile)//works
{
    string garbage;
	const int size= 200;
    char data[size];

	inFile >> garbage;
	inFile.getline(data, size);
	Name=strip_ws(data); //remmove the white space problem

	inFile >> garbage;
	inFile.getline(data, size);
	Desc=data;

}

bool Object::bisObjectUsed()
{
	return bUsedState;
}


//new objects
//KEY
//*****************************************************************
Key::Key(string sName, string sDesc):Object(sName,sDesc)//key constructor
{
}

//*****************************************************************

//new objects
//Door
//*****************************************************************
//door as boolean value which tells if the door is open or not
Door::Door(const string& sName,const string& sDesc,bool bLocked):Object(sName,sDesc)//key constructor
{
	bDoorLockedStatus=bLocked;
}

bool Door::getDoorLockedStatus()
{
	return bDoorLockedStatus;
}

//*****************************************************************


//new objects
//Cup
//*****************************************************************
Cup::Cup(string sName, string sDesc):Object(sName,sDesc)//key constructor
{
}

//*****************************************************************

//new objects
//Note
//*****************************************************************
Note::Note(string sName, string sDesc):Object(sName,sDesc)//key constructor
{
}

//*****************************************************************


//new objects
//letter
//*****************************************************************
Letter::Letter(string sName, string sDesc):Object(sName,sDesc)//key constructor
{
}

//*****************************************************************