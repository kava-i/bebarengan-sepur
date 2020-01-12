#include "CItem.hpp"

// *** GETTER *** //
string CItem::getName()  { return m_sName; }
string CItem::getID()    { return m_sID; }
string CItem::getDescription() { return m_sDescription; }
size_t CItem::getValue() { return m_value; }
bool CItem::getHidden()  { return m_hidden; }



// ********** FIXXEDITEMS ********** //

CFixxedItem::CFixxedItem(string sName, string sID, string sDescription, objectmap characters, objectmap items)
{
    m_sName = sName;
    m_sID = sID;
    m_sDescription = sDescription;
    m_value = 0;
    m_hidden = false;
    m_moveable = false;
    m_characters = characters;
    m_items = items;
}

// *** GETTER *** //
CFixxedItem::objectmap& CFixxedItem::getCharacters() { return m_characters; }
CFixxedItem::objectmap& CFixxedItem::getItems()      { return m_items; }
    




