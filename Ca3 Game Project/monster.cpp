#include <string>
#include <vector>
#include "monster.h"
#include "functions.h"
#include "character.h"

Monster::Monster()
{
	Name="Default Monster";
	sDescription="Default Monster Description";
	sClassName="Default Class";
	health=10;
	minAttack=1;
	maxAttack=2;
	xpValue=5;
}

Monster::Monster(const string& name,string sDesc,string sClass,int hp,int min,int max,int xp)
{
	Name=name;
	sDescription=sDesc;
	sClassName=sClass;
	health=hp;
	minAttack=min;
	maxAttack=max;
	xpValue=xp;
}
	//methods
string Monster::getName()
{
	return Name;
}

string Monster::getDescription()
{
	return sDescription;
}

int Monster::getHealth()
{
	return health;
}

//kills a monster, for testing
void Monster::kill()
{
	health=0;
}


bool Monster::isDead()
{
	if(health>0)
		return false;
	else
		return true;
}

void Monster::TakeDamage(int dmg)
{
	if(dmg>0 && health-dmg>0)
	{
		health=health-dmg;
	}
	else
	{
		health=0;
	}
}

//causes problem
void Monster::attackPlayer(Character& character)
{
	int r=getRandomNumberinRange(minAttack,maxAttack);	
	character.TakeDamage(r);
	cout << "=========================================================="<<endl;
	cout << "Monster: attacks you for " << r << endl;
	cout << "You: have " << character.getHealth() <<  " health."<< endl;
	cout << "=========================================================="<<endl;
}

int Monster::getXPReward()
{
	return xpValue;
}

void Monster::Save(ofstream& outFile)
{
	outFile << "Name= " << Name << endl;
    outFile << "Description= " << sDescription<< endl;
	outFile << "ClassName= " << sClassName << endl;
	outFile << "Health= " << health << endl;
	outFile << "minAttack= " << minAttack<< endl;
	outFile << "maxAttack= " << maxAttack << endl;
	outFile << "XPValue= " << xpValue << endl;
    outFile << endl;
}

void Monster::Load(ifstream& inFile)
{
    string garbage;
	const int size= 600;
    char data[size];

	//name
	inFile >> garbage;
	inFile.getline(data, size);
	Name=data;
	//sDescription
	inFile >> garbage;
	inFile.getline(data, size);
	sDescription=data;
	//sClassName
	inFile >> garbage;
	inFile.getline(data, size);
	sClassName=data;
	//health
	inFile >> garbage >> health; //works
	//minattack
	inFile >> garbage >> minAttack; //works
	//maxattack
	inFile >> garbage >> maxAttack; //works
	//xpvalue
	inFile >> garbage >> xpValue; //works
  
}

void Monster::displayStats()
{
	cout << "Name= " << Name << endl;
    cout << "Description= " << sDescription<< endl;
	cout << "ClassName= " << sClassName << endl;
	cout << "Health= " << health << endl;
	cout << "minAttack= " << minAttack<< endl;
	cout << "maxAttack= " << maxAttack << endl;
	cout << "XPValue= " << xpValue << endl;
    cout << endl;
}