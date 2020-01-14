#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <filesystem>
#include <streambuf>
#include "CWorld.hpp"
#include "CRoom.hpp"
#include "CDetail.hpp"
#include "CPerson.hpp"
#include "CPlayer.hpp"
#include "CCharacter.hpp"
#include "CAttack.hpp"
#include "CFight.hpp"
#include "CDialog.hpp"
#include "CCommandParser.hpp"
#include "json.hpp"
#include "fuzzy.hpp"

//#include <Python.h>

using std::string;
using std::map;
using std::vector;

class CGame
{
private:

    map<string, CPlayer*> m_players;
    CPlayer* m_curPlayer;
    CWorld* m_world;

    typedef map<string, vector<void(CGame::*)(string)>>eventmanager; 
    eventmanager m_eventmanager;

    bool m_endGame;

public: 
    CGame();
   
    // *** FACTORYS *** // 
    void playerFactory();

    string play(string sInput, string sPlayerID);

    // *** Event Manager function *** // 
    typedef std::pair<string, string> event;
    void throw_event(event newEvent);

    // *** EVENTHANDLERS *** // 
    void show       (string sIdentifier);
    void lookIn     (string sIdentifier);
    void take       (string sIdentifier);
    void use        (string sIdentifier);
    void goTo       (string sIdentifier);
    void startDialog(string sIdentifier);
    void callDialog (string sIdentifier);
    void callFight  (string sIdentifier);
    void help       (string sIdentifier);
    void error      (string sIdentifier);
    void deleteCharacter (string sIdentifier);
    
    //Dialogs
    void pissingman_fuckoff(string sIdentifier);

    //Rooms
    void firstZombieAttack(string sIdentifier);

    // *** various functions *** //
    typedef map<string, string> objectmap;
    string getObject(objectmap& mapObjects, string sIdentifierr);


    /*
    //Convert yaml to json
    void toJson(string filename);
    */
};
    





