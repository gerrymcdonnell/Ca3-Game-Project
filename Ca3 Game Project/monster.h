#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <vector>
#include <iostream>


using namespace std;

class Character;

class Monster
{
public:
	Monster();
	Monster(const string& name,string sDescription,string sClass,int hp,int min,int max,int xp);
	//methods
	string getName();
	string getDescription();	
	int getXPReward();
	int getHealth();
	bool isDead();
	void TakeDamage(int dmg);

	//problem here comment out to compile
	void attackPlayer(Character& character);
	void kill();
	//load and save a monster
	void Save(ofstream& outFile);
	void Load(ifstream& inFile);
	void displayStats();

private:
	string Name;
	string sDescription;
	string sClassName;
	int health;
	int minAttack;
	int maxAttack;
	int xpValue;
	
};
#endif