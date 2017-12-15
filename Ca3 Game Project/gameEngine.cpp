
#include "character.h"
#include "room.h"
#include "object.h"
#include "functions.h"
#include "puzzles.h"
#include "quicksave.h"
#include "monster.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()

using namespace std;

//===================================================
//variables
//===================================================
const string TEXT_SEP="=========================================";
//===================================================
//File Names
//===================================================
const string ROOM_FILE="rooms.txt";
const string MONSTERS_FILE="monsters.txt";
const string OBJECT_FILE="objects.txt";
const string QUICKSAVE_FILE="quicksave.txt";
const string FULLSAVE_FILE="fullsave.txt";

//===================================================
//vectors
//===================================================
vector<Room> GameRooms;
vector<Object> GameObjects;
vector<Monster> GameMonsters;

vector<string> sCommands;
vector<string> sCreateableObjects;

//===================================================
//testing methods
//===================================================
 void testCharacter();
 void testRoom();
 void testObjects();
 void testCommands();
 void teststringSplit();
 void testMonsters();

//===================================================
//Game Engine Methods
//===================================================
void loadRooms();
int loadObjects();
string getRoomName(int n);
int getRoomTotal(); //calc how many rooms there are to load
int getObjectTotal();

//puzzles
//===================================================
Puzzles GamePuzzles;
void startRandomPuzzle();
//===================================================

//Monsters
void checkForMonsters();
void LoadMonsters();
int getMonstersTotal(); 

//SAVE METHODS
//===================================================
void LoadQuickSave();
void SaveQuickSave();

void SaveGame();
void LoadGame();
//===================================================

//ask for input and create a room
void createRoom();
bool movetoRoom(int iRoomNum);
bool isValidRoomNum(int n);


//user commands
//===================================================
string getUserCommand(); //get the users command
void processUserCommand(string s,Room r,Character &c);
void setupUserObjects();
//setup a vector of all creatable useable objects
void setupCommands();
//print list of user commands eg for help
void printUserCommands();
//===================================================

int iCountLinesinFile(string sFile);
string sAskUserForString(string sMsg);

//parse the room Desc string for objects i.e words with [] eg [key]
void CreateRoomObjects(string stmp,Room& r);
//current room number
int CurrentRoomNum;
int CurrentMonster;

//character object and current monster object
Character m_player;
Monster m_monster;

int main()
{
	string s="";
	int iLoadedObjects=0;
	int iRoomNum=0;

	//for random number
	srand((unsigned)time(NULL)); 

	printString("ENGINE: Initializing Engine Data..");
	
	//engine init
	//===================================================
	//setup the command vector with valid commands
	printString("ENGINE: Loading User Commands..");
	setupCommands();

	//seup usable objects
	printString("ENGINE: Loading Objects..");
	setupUserObjects();
	//load objects from file
	iLoadedObjects=loadObjects();
	cout << "ENGINE: Loaded " << iLoadedObjects << " Objects" << endl;

	printString("ENGINE: Loading Rooms..");
	//load rooms
	loadRooms();

	//Load each room with an object if there is one in the room file
	//===================================================
	string sDesc="";
	for(int i=0;i<GameRooms.size();i++)
	{
		sDesc=GameRooms[i].getDesc();
		CreateRoomObjects(sDesc,GameRooms[i]);
	}
	printString("Done Setting up Rooms.");
	//===================================================

	//Puzzles
	//===================================================
	printString("ENGINE: Setting up puzzles.");
	GamePuzzles= Puzzles();
	printString("ENGINE: Loaded Puzzles.");
	//===================================================


	//Monsters
	//===================================================	
	printString("ENGINE: Loading Monsters.");
	LoadMonsters();
	printString("ENGINE: Loaded Monsters.");
	//===================================================	


	//show game title etc	
	//===================================================	
	//start game
	//***************************************************************
	printString("");
	printString("");
	printString("");
	printString("\t\t\tWelcome to 'Text Adventure Game v2.0 -8/dec/2010'");
	printString("\t\t\tBy:gerry mc donnell 2010\n");
	
	printString("Here is a list of User Commands available in Game:");
	printString("\n\nTIP: Type 'moveto 'roomexit' Where 'roomexit' is a exit number in a room.");
	printString("TIP: Objects in a room appear with [ ] surounding them.");
	
	//print list of user commands
	printUserCommands();

	//setup character
	//===================================================
	printString("ENGINE: Setting up character.");
	m_player=Character();
	m_player.CreateNewCharacter();
	//===================================================

	printString("\n\nINTRO:");
	cout << m_player.getName() << " wake's up with a terrable headache in the middle of nowhere. Youve no idea how you got here or where to go next. Theres nobody around as you look far into the distance."<<endl;

	//display first room
	GameRooms[0].displayRoom();

	//prompt user for commands
	s=getUserCommand();

	//while user doenst type quit keep processing commands
	while(s!="quit")
	{
		processUserCommand(s,GameRooms[CurrentRoomNum],m_player);		
		
		//Random game events
		//=================================================
		//add in for release version

		//check for a monster
		checkForMonsters();
		//random puzzle
		startRandomPuzzle();
		//=================================================

		//prompt user for commands
		s=getUserCommand();

	}
	//End of game Loop
	//===========================================================================
	

	

	printString("===========================================================================");
	printString("Exiting Game");
	printString("===========================================================================");
	getchar();
	return 0;

}


//***********************************************************************
//ENGINE METHODS
//***********************************************************************

//starts a random Puzzle
void startRandomPuzzle()
{
	int n=irandomNumber(8);
	int XPReward=getRandomNumberinRange(15,30);

	switch(n)
	{
	case 0:
		cout << "==============================" << endl;
		cout << "Puzzle: Guess the Blank Word."<< endl;
		cout << "==============================" << endl;
		GamePuzzles.GuesstheBlankWord();
		break;
	case 1:
		cout << "==============================" << endl;
		cout << "Puzzle: Guess the Missing Number."<< endl;
		cout << "==============================" << endl;
		GamePuzzles.GuessTheLockCombination();
		break;
	case 2:
		cout << "==============================" << endl;
		cout << "Puzzle: Guess the Scrambled Word."<< endl;
		cout << "==============================" << endl;
		GamePuzzles.GuesstheScrambledWord();
		break;
	case 3:
		cout << "==============================" << endl;
		cout << "Puzzle: Solve the Maths Problem."<< endl;
		cout << "==============================" << endl;
		GamePuzzles.SolveTheMathsProblem();
		break;
	case 4:
		cout << "==============================" << endl;
		cout << "Puzzle: Complete the Phrase."<< endl;
		cout << "==============================" << endl;
		GamePuzzles.SolveThePhrase();
		break;
	case 5:
		//no puzzle
		break;
	case 6:
		//no puzzle
		break;
	case 7:
		//no puzzle
		break;
	case 8:
		//no puzzle
		break;
	}

	if(n>=0 && n<5)
	{
		//apply xp reward
		m_player.addExp(XPReward);
	}
}


//allows user to enter data for a room
//unused function
void createRoom()
{
	Room r=Room();

	int n=0;
	string sName="";
	string sDesc="";

	//ask user for input
	//save the room
	cout << "Room Editor:" <<endl;
	cout << TEXT_SEP<<endl;
	

	cout << "Enter Room Number: ";
	cin >> n;
	getchar();

	sName=sAskUserForString("Enter Room Name: ");	
	//getchar();

	sDesc=sAskUserForString("Enter Room Description: ");
	//getchar();
	

	//set room variables
	r.setNum(n);
	r.setName(sName);
	r.setDesc(sDesc);

	r.displayRoom();

	//save the data to file
	ofstream outFile;
	outFile.open(ROOM_FILE.c_str(), ios::app); //append to file

	r.save(outFile);
	outFile.close();
	
}


//calc the number of rooms load in a file
//if one room has 3 lines + a line space and the end of the file has blank line also
int getRoomTotal() //works
{
	int iTotal=0;
	int n=iCountLinesinFile(ROOM_FILE)-1;

	iTotal=n/5;

	//cout << "There are " << iTotal << " rooms" << endl;
	return iTotal;
}

int getMonstersTotal() //works
{
	int iTotal=0;
	int n=iCountLinesinFile(MONSTERS_FILE)-1;

	iTotal=n/8;

	//cout << "There are " << iTotal << " Monsters." << endl;
	return iTotal;
}

string getRoomName(int n)
{
	return GameRooms[n].getName();
}


//count objects in a file
int getObjectTotal() //works
{
	int iTotal=0;
	int n=iCountLinesinFile(OBJECT_FILE)-1;

	iTotal=n/3;

	//cout << "There are " << iTotal << " objects" << endl;
	return iTotal;
}


//load rooms from a text file here and create a collection of rooms for the game
void loadRooms()
{
	//code works
	ifstream inFile (ROOM_FILE.c_str()); //open input file
	Room r=Room();

	//get the number of rooms first
	int iRoomTotal=getRoomTotal();

	if(iRoomTotal>0)
	{
		for(int i=0;i<iRoomTotal;i++)
		{
			//add room to vector
			r.load(inFile);
			GameRooms.push_back(r);

			//create the objects needed for this room

		}
	}
	else
	{
		//serious error no rooms to load
		cout << "ERROR: Unable to load room file."<< endl;
	}

}


void LoadMonsters()
{

	ifstream inFile (MONSTERS_FILE.c_str()); //open input file
	Monster m=Monster();

	//get the number of monsters first
	int iMonsterTot=getMonstersTotal();
	if(iMonsterTot>0)
	{
		for(int i=0;i<iMonsterTot;i++)
		{
			m.Load(inFile);
			//for debug
			m.displayStats();
			GameMonsters.push_back(m);
		}
	}
	else
	{
		//serious error no monsters to load
		cout << "ERROR: Unable to load Monsters file."<< endl;
	}
	cout << "Loaded " << iMonsterTot << " Monsters." << endl;
}

//not will need to be able to handle spaces 
//i.e open door etc
string getUserCommand()//works
{
	string sCmd="";
	cout << "Enter Command:>> " ;	
	getline(cin,sCmd);
	//cout << "Command entered: " << sCmd <<endl;
	return sCmd;
}



//take user string and do stuff
void processUserCommand(string s,Room r,Character &player)
{
	vector <string> stmp;
	string sCmd="";
	string sObject="";
	Object Obj=Object();
	int totalRoomObjects=0;
	int iObj=0;

	StringSplit(s, " ", stmp);

	if(stmp.size()>1 ) //user has enter more than 2 words eg "open door"
	{

		//get the command and object
		sCmd=stmp[0];
		sObject=stmp[1];

		//search for the object
		totalRoomObjects=r.getNumRoomObjects();

		//cout << "Total Objs in room: " << totalRoomObjects << endl;

		if(totalRoomObjects!=0)
		{
			//room has an object in it get the object
			iObj=r.searchRoomForObject(sObject);
			if(iObj!=-1 || sCmd=="moveto")
			{

				//a command no argument i.e no object was entered
				if(sCmd!="moveto")
				{
					Obj=r.getRoomObject(iObj);
				}
				///////////////////////////////////////////////////////////////////
				//search command list for entered command
				if(searchVectorForString(sCommands,sCmd)==true)
				{
						if(sCmd=="examine") 
						{
							//get the object to interact with
							//printString("you examine the " + sObject);
							cout << Obj.examine() <<endl;
						}
						else if (sCmd=="open")
						{
							//printString("you open the " + sObject);
							cout<< Obj.examine()<<endl;
						}
						else if (sCmd=="use")
						{
							printString("you use the " + sObject);
							//Obj.useWith(objHere);
						}
						else if (sCmd=="read")
						{
							cout << Obj.read() <<endl;
						}
						else if (sCmd=="pickup")
						{
							//add object to player inventory
							player.addObject(Obj);
							printString("You pick up the " + sObject);
						}
						else if (sCmd=="moveto" )
						{
							//move to room number
							int nRoomNumExit=GetIntVal(sObject);
							if(isValidRoomNum(nRoomNumExit)==true && r.bIsValidExit(nRoomNumExit)==true)
							{
								printString("Displaying Room.." + nRoomNumExit);
								GameRooms[nRoomNumExit].displayRoom();
								CurrentRoomNum=nRoomNumExit;
								//do a quick save
								SaveQuickSave();
							}
							else
							{
								printString("ERROR: Invalid Exit or Room");
							}
						}
						else
						{
							//user enter either one word or an invalid command
							printString("ERROR: Command not found.");
						}
				//////////////////////////////////////////////////////////////
				}
			}
		}
	}
	else
	{
		//user enter either one word or an invalid command
		if(s=="help")
		{
			printString("List of Valid Game Commands:");
			printUserCommands();
			printString("Example Usage <Command> <objectname>");
		}

		else if(s=="quit")
			printString("Exiting Game.");

		else if(s=="showroom")
		{
			GameRooms[CurrentRoomNum].displayRoom();
		}
		else if (s=="displaybackpack")
		{
			player.displayInventory();
		}
		else if (s=="displaystats")
		{
			player.displayCharacterStats();
		}
		//save and load game
		else if (s=="savegame")
		{
			cout << s<< endl;
			SaveGame();
		}
		else if (s=="loadgame")
		{
			cout << s<< endl;
			LoadGame();
		}
		else if (s=="quicksave")
		{
			SaveQuickSave();
			cout << "QuickSaved Game."<<endl;
		}
		else if (s=="quickload")
		{
			cout << s<< endl;
			LoadQuickSave();
		}
		else
		{
			printString("ERROR: Please enter a valid Command.");
		}
	}

}


//setup the commands needed in the game
void setupCommands()
{
	sCommands.push_back("use");
	sCommands.push_back("open");
	sCommands.push_back("examine");
	sCommands.push_back("read");
	sCommands.push_back("moveto");
	sCommands.push_back("help");
	sCommands.push_back("quit");
	sCommands.push_back("showroom");

	//new commands
	sCommands.push_back("pickup");
	sCommands.push_back("displaybackpack"); //show player invent
	sCommands.push_back("displaystats");

	sCommands.push_back("savegame");
	sCommands.push_back("loadgame");
	sCommands.push_back("quicksave");
	sCommands.push_back("quickload");
}

//a vector that contains a list of createable objects
void setupUserObjects()
{
	sCreateableObjects.push_back("door");
	sCreateableObjects.push_back("key");
	sCreateableObjects.push_back("letter");
	sCreateableObjects.push_back("mailbox");
	sCreateableObjects.push_back("note");
	sCreateableObjects.push_back("cup");
	sCreateableObjects.push_back("food");
}



//exit a room, passin the room number to move to
bool movetoRoom(int iRoomNum)
{
	cout << "Moving to Room Number " << iRoomNum<<endl;
	//do more stuff
	//create room object
	//display it
	if(iRoomNum<GameRooms.size())
	{
		//display room
		GameRooms[iRoomNum].displayRoom();
		return true;
	}
	else
	{
		printString ("Error Invalid Room Number.");
		return false;
	}


}

//count the number  of lines in a file
//note c++ adds a space after each save on object and and extra line at the end
//so 2 objects will have 9 lines
//and one object will have 5 (3 lines , space and marker at end of file)
int iCountLinesinFile(string sFile)//works
{
	string line;
	int i=0;

	ifstream myfile;

	myfile.open(sFile.c_str());//.c_str allows you to pass a string in here
	if (myfile.is_open())
	{
		while ( myfile.good() )
		{
		  getline (myfile,line);
		  i++;
		}
	myfile.close();	 
	}
	return i;   
}

string sAskUserForString(string sMsg)
{
	string stemp;
	cout << sMsg;
	getline(cin,stemp); //cin doest work with spaces
	return stemp;
}


//load in the objects file of objects
int loadObjects()
{
	int iCount=0;
	ifstream inFile (OBJECT_FILE.c_str());

	int numObjects=getObjectTotal();
	Object obj=Object();

	for(int x=0;x<numObjects;x++)
	{
		obj.load(inFile);
		//add objects to game engine vector
		printString("Loading Object: " + obj.getName());
		GameObjects.push_back(obj);
		iCount++;
	}
	return iCount;
}


//search a string for [] and put these items in a vector
void CreateRoomObjects(string stmp,Room& r)
{				   //4   8
	//string stmp="the [cat] and [dog] ran .";
	
	//PART 1
	string s="";
	vector <string> sObjectsFound;

	int start;
	int end;
		
	start=stmp.find("[");
	end=stmp.find("]");


	while(stmp.find("]")!=-1)
	{
		start=stmp.find("[");
		end=stmp.find("]");

		for(int x=start+1;x<=end-1;x++)
		{
			s+=stmp[x];
		}
		
		sObjectsFound.push_back(s);		

		//remove the brackets so next work appears
		stmp[start]='-';
		stmp[end]='-';

		s="";		
	}

	//PART 2
	//==================================================
	//create valid objects, loop throught the found objects
	//see if there valid objects and
	//create objects based on whats in the text file
	string sObj="";
	int iObj;

	//key door,cup, note mailbox
	for(int i=0;i<sObjectsFound.size();i++)
	{
		sObj=sObjectsFound[i];
		//printString("Found " + sObj);

		//key, door, cup, note letter
		//object is valid create it
		//search the gameobject vector for this object and add it to the room
		//search GameObjects for object and put it in the room
		iObj=searchVectorForObject(GameObjects,sObj);

		//1 check the object name, 
		//2 make the object and 
		//3 add to the room

		if(iObj!=-1) //if its a valid object
		{
			if(sObj.compare("key")==0)
			{
				//object is loaded in the game engine add it to the room
				//create obj
				//get the object and add to room
				Object obj=GameObjects[iObj];
				r.addObject(obj);

			}
			else if(sObj.compare("note")==0)
			{
				//get the object and add to room
				Object obj=GameObjects[iObj];
				r.addObject(obj);
			}

			else if(sObj.compare("mailbox")==0)
			{
				//get the object and add to room
				Object obj=GameObjects[iObj];
				r.addObject(obj);
			}
			else if(sObj.compare("cup")==0)
			{
				//get the object and add to room
				Object obj=GameObjects[iObj];
				r.addObject(obj);
			}
			else if(sObj.compare("food")==0)
			{
				//get the object and add to room
				Object obj=GameObjects[iObj];
				r.addObject(obj);
			}
			else if(sObj.compare("door")==0)
			{
				//get the object and add to room
				//Door d=Door("Door","An old wooden Door",false);
				Object obj=GameObjects[iObj];
				r.addObject(obj);
			}
			
			else
			{
				printString("Object " + sObj + " not found, not a valid object");
			}
		}
	}//end of for

}

bool isValidRoomNum(int n)
{
	if(n>-1  && n<GameRooms.size())
		return true;
	else
		return false;
}

//print list of commands for user to get help
void printUserCommands()
{
	for(int x=0;x<sCommands.size();x++)
	{
		printString(sCommands[x]);
	}
}


//NEW FEATURES for ca3
//***********************************************************************
void SaveGame()
{
	//FULLSAVE_FILE
	//eg FullSaveGame f1=FullSaveGame(1,"gerry",34,"warlock",99,vObjects);

	FullSaveGame f1=FullSaveGame(CurrentRoomNum,m_player.getName(),
		m_player.getExp(),
		m_player.getClassName(),
		m_player.getHealth(),
		m_player.getInventory());

	ofstream outFile (FULLSAVE_FILE.c_str());
	f1.SaveGame(outFile);
	outFile.close();
}

void LoadGame()
{
	//FULLSAVE_FILE
	FullSaveGame f1=FullSaveGame();
	ifstream inFile (FULLSAVE_FILE.c_str());

	f1.LoadGame(inFile);	
	f1.display();
	inFile.close();

	//apply data to game
	CurrentRoomNum=f1.getRoomNum();

	m_player.setName(f1.getPlayerName());
	m_player.setExp(f1.getPlayerXP());
	m_player.setClassName(f1.getPlayerClass());
	m_player.setHealth(f1.getCharacterHP());
	f1.getCharacterInventory(m_player);

	//go to the room loaded
	GameRooms[CurrentRoomNum].displayRoom();
	

}

void LoadQuickSave()
{
	//QUICKSAVE_FILE
	QuickSave q1=QuickSave();
	ifstream inFile (QUICKSAVE_FILE.c_str());
	q1.LoadQuickSave(inFile);
	inFile.close();

	cout <<"Loading QuickSave Game:"  << endl;
	q1.display();
	

	//apply data to game
	CurrentRoomNum=q1.getRoomNum();

	m_player.setName(q1.getPlayerName());
	m_player.setExp(q1.getPlayerXP());
	m_player.setClassName(q1.getPlayerClass());
	m_player.setHealth(50);
	
	//go to the room loaded
	GameRooms[CurrentRoomNum].displayRoom();
	
}

//works
void SaveQuickSave()
{
	//QUICKSAVE_FILE
	//ex QuickSave(1,"gerry",34,"warlock");
	ofstream outFile (QUICKSAVE_FILE.c_str());

	QuickSave q2=QuickSave(CurrentRoomNum,
		m_player.getName(),
		m_player.getExp(),
		m_player.getClassName());

	//q2.display();
	q2.SaveQuickSave(outFile);
	cout <<"GAME ENGINE: Saving Game check Point."<< endl;
	outFile.close();
}


//monster function
void checkForMonsters()
{
	//random chance of a monster
	int n=irandomNumber(4);

	int totalMonsters=GameMonsters.size()-1;
	if(n==1)
	{
		//get a random monster from the loaded monsters
		CurrentMonster=irandomNumber(totalMonsters);
		m_monster=GameMonsters[CurrentMonster];

		//theres a monster
		bool bRunAway=false;
		bool bDeadMonster=false;
		
		cout << "ALERT!: Youve spotted a monster."<<endl;
		cout << endl;

		bRunAway=m_player.attackMonster(m_monster);
		while(bRunAway==false && bDeadMonster==false)
		{
			//monster attacks player
			m_monster.attackPlayer(m_player);
			bDeadMonster=m_monster.isDead();
			bRunAway=m_player.attackMonster(m_monster);
		}
		//fights over player ran away
		//is monster dead
		if(m_monster.isDead()==true)
		{
			int xpReward=m_monster.getXPReward();
			cout << "You earned " << xpReward << " XP!!" << endl;
			m_player.addExp(xpReward);
		}
	}
	else
	{
		//no monster!
	}

}

//***********************************************************************






//TESTING
void testMonsters()
{
	//create a monster
	Monster m1 =Monster("Orc","An ordinary Orc","Warrior",50,1,5,50);
	Monster m2 =Monster("Troll","A very tall troll","Warrior",25,1,6,50);
	Monster m3 =Monster("Goblin","A small green Goblin","Warrior",25,2,6,20);

	m1.displayStats();
	m2.displayStats();

	ofstream outFile(MONSTERS_FILE.c_str());
	ifstream inFile(MONSTERS_FILE.c_str());

	m1.Save(outFile); //save works
	m2.Save(outFile);
	m3.Save(outFile);

	//test monster load
	//m2.Load(inFile);

	cout << "There are " << getMonstersTotal() << " Monsters." << endl;

	/*//create character
	Character c1=Character();//,0,75,5,9);
	c1.SetupCharacter("chuckie",1);

	//show player stats
	c1.displayCharacterStats();


	bool bRunAway=false;
	bool bDeadMonster=false;


	bRunAway=c1.attackMonster(m1);
	while(bRunAway==false && bDeadMonster==false)
	{
		//monster attacks player
		m1.attackPlayer(c1);
		bDeadMonster=m1.isDead();
		bRunAway=c1.attackMonster(m1);
	}
	//fights over player ran away
	//is monster dead

	if(m1.isDead()==true)
	{
		int xpReward=m1.getXPReward();
		cout << "You earned " << xpReward << " XP!!" << endl;
		c1.addExp(xpReward);
	}

	c1.displayCharacterStats();*/
}


//***********************************************************************
//testing created objects
void testObjects()
{
	//works
	/*cout<< "testing object" << endl;
	Object o=Object();

	Object o1=Object("Priceless Ming Vase","It Looks old, it might be worth something.");
	o1.displayObject();
	cout << TEXT_SEP<< endl;*/


	/*cout<< "testing object key" << endl;
	Key k=Key("old key","Its rusty but it looks alright");
	k.displayObject();
	cout << k.examine();*



	//door
	/*Door d=Door("Door","An old wooden Door",false);
	if(d.getDoorLockedStatus()==true)
	{
		cout << "The door is locked." << endl;
	}
	else
	{
		cout << "The door is Open." << endl;
	}
	cout << d.examine();*/




	//test file Io
	//code to use here
	//////////////////////////////////////////////////
	ifstream inFile ("objects.txt");

	int numObjects=getObjectTotal();
	Object obj=Object();

	for(int x=0;x<numObjects;x++)
	{
		obj.load(inFile);
		obj.displayObject();
	}
	///////////////////////////////////////////////////


	//this works and loads in 4 objects from file
	//********************************************************
	/*Object o=Object();
	o.load(inFile);
	o.displayObject();

	Object o1=Object();
	o1.load(inFile);
	o1.displayObject();

	Object o2=Object();
	o2.load(inFile);
	o2.displayObject();

	Object o3=Object();
	o3.load(inFile);
	o3.displayObject();*/
	//********************************************************
	
	




	//fileio
	//create output stream
    /*ofstream outFile("objects.txt");

    //if the file opened correctly
    if(outFile) //is true
    {
        //dump data
        k.save(outFile);
        d.save(outFile);

        //close file
        outFile.close();
    }*/
    
}

void testCharacter()
{
	cout << TEXT_SEP<< endl;
	cout<< "testing a character" << endl;
	Character c =Character("test");
	cout << "Name: " << c.getName() << endl;
	cout << TEXT_SEP<< endl;
}

//test out our room
//test the vectors of exits and objects
void testRoom()
{
	//room exit vector
	//==============================================================================================================================
	vector<int> tmpExits;	
	tmpExits.push_back(2);	
	tmpExits.push_back(3);
	tmpExits.push_back(4);

	//room obj vector
	//==============================================================================================================================
	vector<Object> tmpObjectVector;
	
	Object o=Object("kettle","its rusty");
	tmpObjectVector.push_back(o);
	
	Object o1=Object("door","its old looking");
	tmpObjectVector.push_back(o1);

	Object o2=Object("note","the writing is hard to read");
	tmpObjectVector.push_back(o2);


	cout << TEXT_SEP<< endl;
	cout<< "testing a room" << endl;

	Room r=Room(0,
		"Bed Room",
		"The Room is cold, you look around slowly. A cold breeze of wind hits you neck. You not sure how or why you are here but something tells you that you must get out of here."
		,tmpExits,tmpObjectVector);

	//display room
	r.displayRoom();

	string s1=getUserCommand();
	//processUserCommand(s1);

	//Room r1=Room();
	//r1.displayRoom();
	//==============================================================================================================================
	




	


	//fileio
	//create output stream
    /*ofstream outFile("rooms.txt");

    //if the file opened correctly
    if(outFile) //is true
    {
        //dump data
        r.save(outFile);
		//r1.save(outFile);
        //close file
        outFile.close();
    }*/

}


//test user commands
void testCommands()
{
	string scmd=getUserCommand();
	cout << scmd << endl;

}

void teststringSplit()
{
	vector<string> tmp;
	vector<string> tmp2;
	string data="2 3 4";
	string data2="5 6";

	cout << "string is " << data <<endl;

	//test 1
	StringSplit(data," ",tmp);
	cout << "Found " << tmp.size() << " strings"<<endl;
	for(int x=0;x<tmp.size();x++)
	{
		cout << "results " << tmp[x]<<endl;
	}

	//test 2
	StringSplit(data2," ",tmp2);
	cout << "Found " << tmp2.size() << " strings"<<endl;
	for(int x=0;x<tmp2.size();x++)
	{
		cout << "results " << tmp2[x]<<endl;
	}

}
//***********************************************************************
//***********************************************************************