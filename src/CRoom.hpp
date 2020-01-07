#ifndef CROOM_H
#define CROOM_H

#include <iostream>
#include <string>
#include <map>

class CRoom
{ 
private:
    std::string m_sName;
    std::string m_sDescription;
    
    typedef std::map<std::string, std::string> objectmap;
    objectmap m_exists;
    objectmap m_characters;

public:
    CRoom(std::string sName, std::string sDescription, objectmap exits, objectmap characters);

    // *** getter *** // 
    std::string getName();
    std::string getDescription();
    objectmap& getExtits();
    objectmap& getCharacters();
};
    
#endif
