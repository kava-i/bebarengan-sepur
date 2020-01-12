#include "CRoom.hpp" 

CRoom::CRoom(string sName, string sID, string sDescription, string sEntry, objectmap exits, objectmap characters, std::map<string, CItem*> items)
{
    m_sName = sName;
    m_sID = sID;
    m_sDescription = sDescription;
    m_sEntry = sEntry;
    m_exists = exits;
    m_characters = characters;
    m_items = items;
}


// *** GETTER *** // 

string CRoom::getName()         { return m_sName; }
string CRoom::getID()           { return m_sID; }
string CRoom::getDescription()  { return m_sDescription; }
string CRoom::getEntry()        { return m_sEntry; }
CRoom::objectmap& CRoom::getExtits()        { return m_exists; }
CRoom::objectmap& CRoom::getCharacters()    { return m_characters; }
std::map<string, CItem*>& CRoom::getItems()  { return m_items; }


// *** VARIOUS FUNCTIONS *** //

string CRoom::showEntryDescription(std::map<std::string, CCharacter*>& mapChars)
{
    string sDesc = m_sEntry + m_sDescription + "\n";
    for(auto it : m_characters)
        sDesc.append(mapChars[it.first]->getDescription());

    return sDesc;
}

string CRoom::showDescription(std::map<std::string, CCharacter*>& mapChars)
{
    string sDesc = m_sDescription;
    for(auto it : m_characters) 
        sDesc.append("\n" + mapChars[it.first]->getDescription());

    return sDesc;
}

string CRoom::showExits()
{
    string exits = "Exits: \n";
    size_t counter=1;
    for(auto it : m_exists) {
        exits += std::to_string(counter) + ": " + it.second + "\n";
        counter++;
    }
    return exits;
}
string CRoom::showCharacters()
{
    string characters = "Characters: \n";
    size_t counter=1;
    for(auto it : m_characters) {
        characters += std::to_string(counter) + ": " + it.second + "\n";
        counter++;
    }
    return characters;
}       

string CRoom::showItems()
{
    string items = "Items: \n";
    size_t counter=1;
    for(auto it : m_items) {
        items += std::to_string(counter) + ": "+ it.second->getName() + "\n";
        counter++;
    }
    return items;
} 

