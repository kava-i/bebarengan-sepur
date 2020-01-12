#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <filesystem>
#include "CRoom.hpp"
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
    map<string, CPlayer*>    m_players;
    map<string, CRoom*>      m_rooms;
    map<string, CCharacter*> m_characters;
    map<string, CAttack*>    m_attacks;

    CPlayer* m_curPlayer;

    bool m_endGame;

    typedef map<string, vector<void(CGame::*)(string)>>eventmanager; 
    eventmanager m_eventmanager;

public: 

    CGame();
   
    // *** FACTORYS *** // 
    typedef map<string, string> objectmap;
    void worldFactory();
    void roomFactory();
    void roomFactory(string sPath);
    void playerFactory();
    void attackFactory();
    void attackFactory(std::string sPath);
    map<string, CAttack*> parsePersonAttacks(nlohmann::json j_person);
    map<string, CItem*>   itemFactory(nlohmann::json j_room);
    objectmap characterFactory(nlohmann::json j_characters);
    SDialog* dialogFactory(string sPath); 


    string play(string sInput, string sPlayerID);

    // *** Event Manager function *** // 
    typedef std::pair<string, string> event;
    void throw_event(event newEvent);

    // *** EVENTHANDLERS *** // 
    void show       (string sIdentifier);
    void lookIn     (string sIdentifier);
    void take       (string sIdentifier);
    void goTo       (string sIdentifier);
    void startDialog(string sIdentifier);
    void callDialog (string sIdentifier);
    void callFight  (string sIdentifier);
    void error      (string sIdentifier);
    void deleteCharacter (string sIdentifier);
    
    //Dialogs
    void pissingman_fuckoff(string sIdentifier);

    //Rooms
    void firstZombieAttack(string sIdentifier);

    // *** various functions *** //
    string getObject(objectmap& mapObjects, string sIdentifierr);

    /*
    //Convert yaml to json
    void toJson(string filename);
    */
};
    





