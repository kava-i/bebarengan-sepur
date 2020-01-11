#ifndef CROOM_H
#define CROOM_H

#include <iostream>
#include <string>
#include <map>
#include "CCharacter.hpp"
#include "fuzzy.hpp"

using std::string;

class CRoom
{ 
private:
    string m_sName;
    string m_sID;
    string m_sDescription;
    string m_sEntry;
    
    typedef std::map<string, std::string> objectmap;
    objectmap m_exists;
    objectmap m_characters;

public:
    CRoom(string sName, string sID, string sDescription, string sEntry, objectmap exits, objectmap characters);

    // *** getter *** // 
    string getName();
    string getID();
    string getDescription();
    string getEntry();
    objectmap& getExtits();
    objectmap& getCharacters();

    // *** various functions *** //
    string showEntryDescription(std::map<string, CCharacter*>& mapChars);
    string showDescription(std::map<string, CCharacter*>& mapChars); 
    string showExits();
    string showCharacters();
};
    
#endif
