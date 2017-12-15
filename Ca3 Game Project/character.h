#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include "object.h"
#include "monster.h"

using namespace std;

class Character
{
public:
	Character();
	Character(const string& name);	
	Character(const string& name,string sClass,int iTotalXP,int iHealth,int iminAttack,int imaxAttack);

	//methods

	//getters
	string getName();//
	string getClassName();//
	int getHealth();//
	int getExp();//
	int getLevelofCharacter();
	
	int getminAttack();
	int getmaxAttack();
	vector <Object> getInventory();

	//setters
	void setName(string sName);
	void setClassName(string sClassName);
	void setExp(int xp);
	void setHealth(int hp);
	void setminAttack(int min);
	void setmaxAttack(int max);

	void setInventory(vector <Object> vInventory);

	//add object inventory
	void addObject(Object o);
	//remove object
	void removeObject(string sObjName);
	//display inventory
	void displayInventory();	
	void displayCharacterStats();
	
	void SetupCharacter(const string& name,int iClass);


	void addExp(int Xp);

	void CreateNewCharacter();

	void TakeDamage(int dmg);

	bool isDead();

	bool attackMonster(Monster& monster);
	

private:
	//data mems
	string Name;
	string sClassName;
	int totalXP;
	int health;
	int minAttack;
	int maxAttack;
	int iLevel;
	//int iHitRating; //improves chance to hit

	//vector of objects
	vector<Object> m_inventory;

};
#endif