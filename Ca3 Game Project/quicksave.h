#ifndef QUICKSAVE_H
#define QUICKSAVE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "object.h"
#include "character.h"

using namespace std;

class QuickSave
{
public:
	QuickSave();
	QuickSave(int roomNum,string playerName,int playerXP,string playerClass);
	void display();
	void SaveQuickSave(ofstream& outFile);
	void LoadQuickSave(ifstream& inFile);

	//getters
	int getRoomNum();
	string getPlayerName();
	string getPlayerClass();
	int getPlayerXP();
	

protected:
	int roomNumber;
	string characterName;
	int characterXP;
	string characterClass;

};

class FullSaveGame : public QuickSave
{
public:
	FullSaveGame();
	FullSaveGame(int roomNum,string playerName,int playerXP,string playerClass,int characterHP,vector <Object> m_inventory);
	void SaveGame(ofstream& outFile);
	void LoadGame(ifstream& inFile);
	void display();
	//getters
	int getCharacterHP();
	//load the objects into the characters backpack
	void getCharacterInventory(Character& c);

private:
	//extra stuff to be saved
	int characterHP;
	vector <Object> m_inventory;
};


#endif
