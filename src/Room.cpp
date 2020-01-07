#include "CRoom.hpp" 

CRoom::CRoom(std::string sName, std::string sDescription, objectmap exits, objectmap characters)
{
    m_sName = sName;
    m_sDescription = sDescription;
    m_exists = exits;
    m_characters = characters;
}


// *** GETTER *** // 

std::string CRoom::getName()        { return m_sName; }
std::string CRoom::getDescription() { return m_sDescription; }
std::map<std::string, std::string>& CRoom::getExtits()    { return m_exists; }
std::map<std::string, std::string>& CRoom::getCharacters(){ return m_characters; }
