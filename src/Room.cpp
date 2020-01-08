#include "CRoom.hpp" 

CRoom::CRoom(std::string sName, std::string sDescription, std::string sEntry, objectmap exits, objectmap characters)
{
    m_sName = sName;
    m_sDescription = sDescription;
    m_sEntry = sEntry;
    m_exists = exits;
    m_characters = characters;
}


// *** GETTER *** // 

std::string CRoom::getName()        { return m_sName; }
std::string CRoom::getDescription() { return m_sDescription; }
std::string CRoom::getEntry() { return m_sEntry; }
std::map<std::string, std::string>& CRoom::getExtits()    { return m_exists; }
std::map<std::string, std::string>& CRoom::getCharacters(){ return m_characters; }


// *** VARIOUS FUNCTIONS *** //

std::string CRoom::showEntryDescription(std::map<std::string, CCharacter*>& mapChars)
{
    std::string sDesc = m_sEntry + m_sDescription + "\n";
    size_t counter=1;
    for(auto it : m_characters) {
        sDesc.append(mapChars[it.first]->getDescription());
        counter++;
    }

    return sDesc;
}

std::string CRoom::showDescription(std::map<std::string, CCharacter*>& mapChars)
{
    std::string sDesc = m_sDescription;
    size_t counter=1;
    for(auto it : m_characters) {
        sDesc.append("\n" + mapChars[it.first]->getDescription());
        counter++;
    }

    return sDesc;
}

std::string CRoom::showExits()
{
    std::string exits = "Exits: \n";
    size_t counter=1;
    for(auto it : m_exists)
        exits += std::to_string(counter) + ": " + it.second + "\n";
    return exits;
}
std::string CRoom::showCharacters()
{
    std::string characters = "Characters: \n";
    size_t counter=1;
    for(auto it : m_characters)
        characters += std::to_string(counter) + ": " + it.second + "\n";
    return characters;
}       

