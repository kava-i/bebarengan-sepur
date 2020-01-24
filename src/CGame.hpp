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
#include "json.hpp"
#include "fuzzy.hpp"
#include "func.hpp"

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

    typedef std::pair<string, string> event;

public: 
    CGame();
   
    // *** FACTORYS *** // 
    void playerFactory();

    string 
    string play(string sInput, string sPlayerID);

    string checkLogin(string sName, string sPassword);

    /*
    //Convert yaml to json
    void toJson(string filename);
    */
};
    





