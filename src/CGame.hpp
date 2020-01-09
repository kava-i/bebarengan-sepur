#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include "CRoom.hpp"
#include "CPlayer.hpp"
#include "CCharacter.hpp"
#include "CCommandParser.hpp"
#include "json.hpp"
#include "fuzzy.hpp"

//#include <Python.h>

class CGame
{
private:
    std::map<std::string, CPlayer*>    m_players;
    std::map<std::string, CRoom*>      m_rooms;
    std::map<std::string, CCharacter*> m_characters;

    CPlayer* m_curPlayer;

    bool m_endGame;

    typedef std::map<std::string, CDState*> dialog;
    typedef std::map<std::string, std::vector<void(CGame::*)(std::string)>>eventmanager; 
    eventmanager m_eventmanager;

public: 

    CGame();
   
    // *** FACTORYS *** // 
    typedef std::map<std::string, std::string> objectmap;
    void worldFactory();
    void roomFactory();
    void playerFactory();
    objectmap characterFactory(nlohmann::json j_characters);
    dialog*   dialogFactory(std::string sPath); 


    std::string play(std::string sInput, std::string sPlayerID);

    // *** Event Manager function *** // 
    typedef std::pair<std::string, std::string> event;
    void throw_event(event newEvent);

    // *** EVENTHANDLERS *** // 
    void show       (std::string sIdentifier);
    void goTo       (std::string sIdentifier);
    void startDialog(std::string sIdentifier);
    void callDialog (std::string sIdentifier);
    void error      (std::string sIdentifier);
    
    void pissingman_fuckoff(std::string sIdentifier);

    // *** various functions *** //
    std::string getObject(objectmap& mapObjects, std::string sIdentifierr);

    /*
    //Convert yaml to json
    void toJson(std::string filename);
    */
};
    





