#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <filesystem>
#include <streambuf>
#include "CRoom.hpp"
#include "CDetail.hpp"
#include "CPerson.hpp"
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

class CWorld
{
private:
    map<string, CRoom*>      m_rooms;
    map<string, CCharacter*> m_characters;
    map<string, CAttack*>    m_attacks;

public:

    CWorld();
    
    // *** GETTER *** //
    map<string, CRoom*>& getRooms() { return m_rooms; }
    map<string, CCharacter*>& getCharacters() { return m_characters; }

    // *** FACTORYS *** // 
    typedef map<string, string> objectmap;
    void worldFactory();
    void roomFactory();
    void roomFactory(string sPath);
    void attackFactory();
    void attackFactory(std::string sPath);
    map<string, CAttack*> parsePersonAttacks(nlohmann::json j_person);
    map<string, CItem*>   itemFactory(nlohmann::json j_room);
    map<string, CDetail*>  detailFactory(nlohmann::json j_room);
    objectmap characterFactory(nlohmann::json j_characters);
    SDialog* dialogFactory(string sPath); 
};
