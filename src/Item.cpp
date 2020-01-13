#include "CItem.hpp"

// *** GETTER *** //
string CItem::getName()  { return m_sName; }
string CItem::getID()    { return m_sID; }
string CItem::getDescription() { return m_sDescription; }
string CItem::getType()  { return m_sType; }
size_t CItem::getValue() { return m_value; }
bool CItem::getHidden()  { return m_hidden; }
bool CItem::getMoveable(){ return m_moveable; }


// *** SETTER *** //
void CItem::setHidden(bool hidden) { m_hidden = hidden; }

std::map<string, string (CItem::*)()> CItem::m_functions = {};
void CItem::initializeFunctions()
{
    m_functions["fixxed"]  = &CItem::fixxed;
    m_functions["equipe"]  = &CItem::equipe;
    m_functions["consume"] = &CItem::consume;
}

string CItem::callFunction() {
    return (this->*m_functions[m_sFunction])();
}

// ********** FIXXEDITEMS ********** //

CFixxedItem::CFixxedItem(string sName, string sID, string sDescription, string sLook, objectmap characters, objectmap items)
{
    m_sName = sName;
    m_sID = sID;
    m_sDescription = sDescription;
    m_sType = "fixxed";
    m_sLook = sLook;
    m_value = 0;
    m_hidden = false;
    m_moveable = false;
    m_characters = characters;
    m_items = items;
    m_sFunction = "fixxed";
}

// *** GETTER *** //
string CFixxedItem::getLook() { return m_sLook; }
CFixxedItem::objectmap& CFixxedItem::getCharacters() { return m_characters; }
CFixxedItem::objectmap& CFixxedItem::getItems()      { return m_items; }
    


// ********** EQUIPPABLEITEMS ********** //

CEquippableItem::CEquippableItem(string sName, string sID, string sDescription, string sType, size_t value,bool hidden)
{
    m_sName = sName;
    m_sID = sID;
    m_sDescription = sDescription;
    m_sType = sType;
    m_value = value;
    m_hidden = hidden;
    m_moveable = true;
    m_sFunction = "equipe";
}

CConsumeableItem::CConsumeableItem(string sName, string sID, string sDescription, string sType, size_t value,bool hidden)
{
    m_sName = sName;
    m_sID = sID;
    m_sDescription = sDescription;
    m_sType = sType;
    m_value = value;
    m_hidden = hidden;
    m_moveable = true;
    m_sFunction = "consume";
}


