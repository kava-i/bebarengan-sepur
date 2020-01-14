#include "CItem.hpp"
#include "CPlayer.hpp"


CItem::CItem(nlohmann::json jAttributes)
{
    m_jAtts = jAttributes;
}

std::map<string, string (CItem::*)(CPlayer* p)> CItem::m_functions = {};
void CItem::initializeFunctions()
{
    m_functions["equipe_weapon"] = &CItem::equipeWeapon;
    m_functions["consume_drug"] = &CItem::consumeDrug;
}

string CItem::callFunction(CPlayer* p) {
    string function = m_jAtts.value("function", m_jAtts["type"]);
    return (this->*m_functions[function])(p);
}

string CItem::equipeWeapon(CPlayer* p)
{
    return "You equiped weapon: " + m_jAtts["name"].get<string>() + ".\n";
}

string CItem::consumeDrug(CPlayer* p)
{
    p->setHighness(p->getHighness() + m_jAtts["effekt"].get<size_t>());
    p->removeItem(m_jAtts["name"]);
    return "You consume drug: " + getAttribute<string>("name") + ". Highness inceased by " + std::to_string(m_jAtts["effekt"].get<size_t>()) + ".\n";
}

