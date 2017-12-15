#include <iostream>
#include "character.h"
#include "functions.h"

using namespace std;

Character::Character()
{
	Name="Default character";
	iLevel=1;
}

Character::Character(const string& name)
{
	Name=name;
	iLevel=1;
}

Character::Character(const string& name,string sClass,int iTotalXP,int iHealth,int iminAttack,int imaxAttack)
{
	Name=name;
	sClassName=sClass;
	totalXP=iTotalXP;
	health=iHealth;
	minAttack=iminAttack;
	maxAttack=imaxAttack;
	iLevel=1;
}


void Character::SetupCharacter(const string& name,int iClass)
{
	Name=name;
	iLevel=1;
	totalXP=0;

	if(iClass==1)
	{
		health=75;
		minAttack=5;
		maxAttack=9;
		sClassName="Warlock";
	}
	else if (iClass==2)
	{
		health=100;
		minAttack=10;
		maxAttack=12;
		sClassName="Warrior";
	}
	else if (iClass==3)
	{
		health=50;
		minAttack=13;
		maxAttack=16;
		sClassName="Rogue";
	}	
}



//ask user for input to create there character
void Character::CreateNewCharacter()
{
	string sName="";
	string sgarbage="";
	cout << "Enter Your Name: ";
	getline(cin, sName);

	//Character selection
	cout << "Please select a character class.." << endl;
	cout << "1)Warlock 2)Warrior 3)Rogue > ";

	int characterNum;
	cin >> characterNum; 

	getline(cin, sgarbage);
	SetupCharacter(sName,characterNum);
}


//add an object to the players inventory
//ie player picks up an object
void Character::addObject(Object o)
{
	m_inventory.push_back(o);
}


void Character::displayInventory()
{
	cout << endl;
	cout << "Found " << m_inventory.size() << " items in your backpack" << endl;
	cout << "Items in your backpack:" << endl;
	cout << "=========================================="<<endl;
	for(int x=0;x<m_inventory.size();x++)
	{
		cout << m_inventory[x].getName() <<endl;
	}
	cout << "=========================================="<<endl;
}
//remove an object from the players inventory
void Character::removeObject(string sObjName)
{

	//do stuff
	for(int x=0;x<m_inventory.size();x++)
	{
		if(m_inventory[x].getName()==sObjName)
			m_inventory.erase(m_inventory.begin()+x);
	}
}

void Character::addExp(int Xp)
{
	cout << "REWARD: You Gained "<< Xp << " XP!"<< endl;
	totalXP+=Xp;
	//update the level
	getLevelofCharacter();
}


void Character::displayCharacterStats()
{
	
	cout << "Displaying Characters Stats:"<< endl;
	cout << "============================"<< endl;
	cout << "Name:            "<< Name<< endl;
	cout << "ClassName:       "<< sClassName<< endl;
	cout << "Health:          "<< health<< endl;
	cout << "XP:              "<< totalXP<< endl;
	cout << "minAttack        "<< minAttack<< endl;
	cout << "maxAttack:       "<< maxAttack<< endl;
	//cout << "Hit Rating:       "<< iHitRating<< endl;
	cout << "Level:           "<< getLevelofCharacter()<< endl;
	cout << "================="<< endl;

}

int Character::getLevelofCharacter()
{
	const int LEVEL2_XP_AMOUNT=50;
	const int LEVEL3_XP_AMOUNT=75;
	const int LEVEL4_XP_AMOUNT=125;
	const int LEVEL5_XP_AMOUNT=150;
	const int LEVEL6_XP_AMOUNT=200;

	int characterLevel=0;

	if(totalXP>-1 && totalXP<LEVEL2_XP_AMOUNT)
	{
		iLevel=1;
	}
	else if(totalXP>=LEVEL2_XP_AMOUNT && totalXP<LEVEL3_XP_AMOUNT)
	{
		iLevel=2;
	}
	else if(totalXP>=LEVEL3_XP_AMOUNT && totalXP<LEVEL4_XP_AMOUNT)
	{
		iLevel=3;
	}
	else if(totalXP>=LEVEL4_XP_AMOUNT && totalXP<LEVEL5_XP_AMOUNT)
	{
		iLevel=4;
	}
	else if(totalXP>=LEVEL6_XP_AMOUNT)
	{
		iLevel=5;
	}

	return iLevel;
}

bool Character::isDead()
{
	if(health>0)
		return false;
	else
		return true;
}

void Character::TakeDamage(int dmg)
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

bool Character::attackMonster(Monster& monster)
{
	int r=0;
	int selection = 1;
	cout << "1) Attack 2) Run > ";
	cin >> selection;
	cout << endl;

	switch(selection)
	{
	case 1:
		r=getRandomNumberinRange(minAttack,maxAttack);	
		monster.TakeDamage(r);	
		cout << "=========================================================="<<endl;
		cout << "You: hit the " << monster.getName() << " for: " << r << " damage." <<endl;
		cout << "Monster: " << monster.getName() << " now has: " << monster.getHealth() << " health." <<endl;
		cout << "=========================================================="<<endl;
		break;

	case 2:
		//25% chance of being able to run
		r = getRandomNumberinRange(1,4);
		if(r == 1)
		{
			cout << "You run away." << endl;
			return true;
		}
		else
		{
			cout << "You could not escape." << endl;
			break;
		}
	}
	return false;

}

//getters
string Character::getName()
{
	return Name;
}

string Character::getClassName()
{
	return sClassName;
}

int Character::getHealth()
{
	return health;
}

int Character::getExp()
{
	return totalXP;
}

int Character::getminAttack()
{
	return minAttack;
}

int Character::getmaxAttack()
{
	return maxAttack;
}


vector <Object> Character::getInventory()
{
	return m_inventory;
}

//setters
void Character::setName(string sName)
{
	Name=sName;
}
void Character::setClassName(string sClass)
{
	sClassName=sClass;
}
void Character::setExp(int xp)
{
	totalXP=xp;
}
void Character::setHealth(int hp)
{
	health=hp;
}
void Character::setminAttack(int min)
{
	minAttack=min;
}
void Character::setmaxAttack(int max)
{
	maxAttack=max;
}