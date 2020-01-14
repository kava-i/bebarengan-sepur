#include "CItem.hpp"
#include "CPlayer.hpp"

// *** GETTER *** //
string CItem::getName()  { return m_sName; }
string CItem::getID()    { return m_sID; }
string CItem::getDescription() { return m_sDescription; }
string CItem::getType()  { return m_sType; }
size_t CItem::getValue() { return m_value; }
bool CItem::getHidden()  { return m_hidden; }


// *** SETTER *** //
void CItem::setHidden(bool hidden) { m_hidden = hidden; }

std::map<string, string (CItem::*)(CPlayer* p)> CItem::m_functions = {};
void CItem::initializeFunctions()
{
    m_functions["equipe_weapon"] = &CItem::equipeWeapon;
    m_functions["consume_drug"] = &CItem::consumeDrug;
}

string CItem::callFunction(CPlayer* p) {
    return (this->*m_functions[m_sFunction])(p);
}


// ********** EQUIPPABLEITEMS ********** //

CEquippableItem::CEquippableItem(string sName, string sID, string sDescription, string sType, size_t value,bool hidden, string sFunction)
{
    m_sName = sName;
    m_sID = sID;
    m_sDescription = sDescription;
    m_sType = sType;
    m_value = value;
    m_hidden = hidden;
    m_sFunction = sFunction;
}

string CEquippableItem::equipeWeapon(CPlayer* p)
{
    return "You equiped weapon: " + m_sName + ".\n";
}

CConsumeableItem::CConsumeableItem(string sName, string sID, string sDescription, string sType, size_t effekt, size_t value, bool hidden, string sFunction)
{
    m_sName = sName;
    m_sID = sID;
    m_sDescription = sDescription;
    m_sType = sType;
    m_effekt = effekt;
    m_value = value;
    m_hidden = hidden;
    m_sFunction = sFunction;
}

string CConsumeableItem::consumeDrug(CPlayer* p)
{
    p->setHighness(p->getHighness() + m_effekt);
    p->removeItem(m_sName);
    return "You consume drug: " + m_sName + ". Highness inceased by " +std::to_string(m_effekt) + ".\n";
}

