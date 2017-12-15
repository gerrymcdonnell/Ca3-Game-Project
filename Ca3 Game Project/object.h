#ifndef OBJECT_H
#define OBJECT_H


//support at least 3 verbs, namely examine, use ... with ... and open.

#include <string>
#include <fstream>

using namespace std;

class Object
{
public:
	Object();
	//virtual ~Object();
	Object(const string& sName,const string& sDesc);

	//methods
	string getName();
	string getDesc();
	void displayObject();
	
	string open();
	string examine();
	string useWith(Object& object);
	string read();

	void save(ofstream& outFile);
	void load(ifstream& inFile);

	bool bisObjectUsed();

	//virtual functions
	/*virtual string examine();
	virtual string open();
	virtual string useWith(Object& object);*/


protected:
	//data mems
	string Name;
	string Desc;
	bool bUsedState;


};



class Key:public Object
{
public:
	Key(string sName, string sDesc);
	~Key();
private:
	
};


class Door:public Object
{
public:
	Door(const string& sName,const string& sDesc,bool bLocked);
	~Door();
	bool getDoorLockedStatus();
	
protected:
	bool bDoorLockedStatus;
	
};


class Cup:public Object
{
public:
	Cup(string sName, string sDesc);
	~Cup();
private:	
};


class Note:public Object
{
public:
	Note(string sName, string sDesc);
	~Note();
private:	
};

class Letter:public Object
{
public:
	Letter(string sName, string sDesc);
	~Letter();
private:	
};



/*class Key : public Object
{
public:
	Key(string name, string descriptions);
	~Key();
	
	//implement interface Object
	string examine()
	{
		return string("This looks like it is a hundred years old");
	}
	
	string open()
	{
		return string("Nothing happens...");
	}
	
	string useWith(Object& object)
	{
		if(object.getName() == "door")
		{
		object.setOpen(true);
		}
	}
};*/


#endif