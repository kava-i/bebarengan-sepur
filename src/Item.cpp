#include "CItem.hpp"
#include "CPlayer.hpp"


CItem::CItem(nlohmann::json jBasic, nlohmann::json jItem)
{
    m_jAtts = jBasic;

    for(auto it=jItem.begin(); it!=jItem.end(); ++it) {
        if(it.key() == "from")
            continue;
        m_jAtts[it.key()] = it.value();
    }
}

// *** GETTTER *** //
string CItem::getID()      { return getAttribute<string>("id"); }
string CItem::getName()    { return getAttribute<string>("name"); }
string CItem::getFunction(){ return m_jAtts.value("function", m_jAtts["type"]); } 
size_t CItem::getEffekt()  { return getAttribute<size_t>("effekt"); }


// Initialize Functions 
std::map<string, void (CItem::*)(CPlayer* p)> CItem::m_functions= {};
void CItem::initializeFunctions()
{
    //Consume-functions
    m_functions["consume_drug"] = &CItem::consumeDrug;

    //Equipe-functions
    m_functions["equipe_weapon"] = &CItem::equipeWeapon;
}

// ***** FUNCTION-CALLER ***** // 

//Consume function
bool CItem::callFunction(CPlayer* p) {
    if(m_functions.count(getFunction()) == 0) 
        return false;
    else
        (this->*m_functions[getFunction()])(p);
    return true;
}


// ***** CONSUME FUNCTIONS ***** //
void CItem::consumeDrug(CPlayer* p)
{
    p->setHighness(p->getHighness() + getEffekt());
    p->removeItem(m_jAtts["name"]);
    p->appendPrint("You consume drug: " + getName() + ". Highness inceased by " + std::to_string(getEffekt()) + ".\n");
}


// ***** EQUIPE-FUNCTIONS ***** //
void CItem::equipeWeapon(CPlayer* p)
{
    std::cout << "CItem::equipeWeapon\n";
    if(p->getEquipment()["weapon"] == NULL)
    {
        std::cout << "Adsding attack... \n";
        p->appendPrint("You equiped weapon: " + getName() + ".\n");
        string sAttack = m_jAtts.value("attack", "");
        if(sAttack != "") {
            std::cout << "1. " << std::endl;
            p->getAttacks()[sAttack] = p->getWorld()->getAttacks()[sAttack];
            std::cout << "2. " << std::endl;
            p->appendPrint("New attack \"" + p->getAttacks()[sAttack]->getName() + "\" added to attack.\n");
        }

        std::cout << "Adding item... \n";
        p->getEquipment()["weapon"] = this;
        std::cout << "It worked ;) \n";
    }

    else if(p->getEquipment()["weapon"]->getID() == getID())
        p->appendPrint("Weapon already equipt.\n");

    else
        p->appendPrint("Already a Weapon equipt, want to change?\n");
}


