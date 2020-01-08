#ifndef CROOM_H
#define CROOM_H

#include <iostream>
#include <string>
#include <map>
#include "CCharacter.hpp"
#include "fuzzy.hpp"

class CRoom
{ 
private:
    std::string m_sName;
    std::string m_sDescription;
    std::string m_sEntry;
    
    typedef std::map<std::string, std::string> objectmap;
    objectmap m_exists;
    objectmap m_characters;

public:
    CRoom(std::string sName, std::string sDescription, std::string sEntry, objectmap exits, objectmap characters);

    // *** getter *** // 
    std::string getName();
    std::string getDescription();
    std::string getEntry();
    objectmap& getExtits();
    objectmap& getCharacters();

    // *** various functions *** //
    std::string showEntryDescription(std::map<std::string, CCharacter*>& mapChars);
    std::string showDescription(std::map<std::string, CCharacter*>& mapChars); 
    std::string showExits();
    std::string showCharacters();
};
    
#endif
