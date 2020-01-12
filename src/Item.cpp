#include "CItem.hpp"

// *** GETTER *** //
string CItem::getName()  { return m_sName; }
string CItem::getID()    { return m_sID; }
string CItem::getDescription() { return m_sDescription; }
size_t CItem::getValue() { return m_value; }
bool CItem::getHidden()  { return m_hidden; }
bool CItem::getMoveable()  { return m_moveable; }


// *** SETTER *** //
void CItem::setHidden(bool hidden) { m_hidden = hidden; }


// ********** FIXXEDITEMS ********** //

CFixxedItem::CFixxedItem(string sName, string sID, string sDescription, string sLook, objectmap characters, objectmap items)
{
    m_sName = sName;
    m_sID = sID;
    m_sDescription = sDescription;
    m_sLook = sLook;
    m_value = 0;
    m_hidden = false;
    m_moveable = false;
    m_characters = characters;
    m_items = items;
}

// *** GETTER *** //
string CFixxedItem::getLook() { return m_sLook; }
CFixxedItem::objectmap& CFixxedItem::getCharacters() { return m_characters; }
CFixxedItem::objectmap& CFixxedItem::getItems()      { return m_items; }
    


// ********** EQUIPPABLEITEMS ********** //

CEquippableItem::CEquippableItem(string sName, string sID, string sDescription, size_t value,bool hidden)
{
    m_sName = sName;
    m_sID = sID;
    m_sDescription = sDescription;
    m_value = value;
    m_hidden = hidden;
    m_moveable = true;
}




