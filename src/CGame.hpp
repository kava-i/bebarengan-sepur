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

//#include <Python.h>

class CGame
{
private:
    std::map<std::string, CRoom*>      m_rooms;
    std::map<std::string, CCharacter*> m_characters;

    CPlayer m_player;

    bool m_endGame;

    typedef std::map<std::string, CDState*> dialog;
    typedef std::map<std::string, std::vector<void(CGame::*)(std::string, std::string)>>eventmanager; 
    eventmanager m_eventmanager;

public: 
    CGame() : m_player("", NULL) {
        m_endGame = false;
        m_player = CPlayer("", NULL);
    }
   
    // *** FACTORYS *** // 
    typedef std::map<std::string, std::string> objectmap;
    void worldFactory();
    void roomFactory();
    objectmap characterFactory(nlohmann::json j_characters);
    dialog dialogFactory(std::string sPath); 


    std::string play(std::string sInput);

    // *** Event Manager function *** // 
    void throw_event(std::pair<std::string, std::string> event);

    // *** EVENTHANDLERS *** // 
    void showExits(std::string sType, std::string sIdentifier);
    void showChars(std::string sType, std::string sIdentifier);
    void goTo(std::string sType, std::string sIdentifier);
    void startDialog(std::string sType, std::string sIdentifier);


    /*
    //Convert yaml to json
    void toJson(std::string filename);
    */
};
    





