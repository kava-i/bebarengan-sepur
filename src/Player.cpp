#include "CPlayer.hpp"

CPlayer::CPlayer(string sName, string sID, int hp, size_t strength, CRoom* room, attacks newAttacks)
{
    m_sName = sName;
    m_sID = sID;
    m_hp = hp;
    m_strength = strength;
    m_room = room;
    m_status = "standard";
    m_attacks = newAttacks;
}

// *** GETTER *** // 
CRoom* CPlayer::getRoom()   { return m_room; }
string CPlayer::getPrint()  { return m_sPrint; }
string CPlayer::getStatus() { return m_status; };
CFight* CPlayer::getFight() { return m_curFight; };

// *** SETTER *** // 
void CPlayer::setRoom(CRoom* room)          { m_room = room; }
void CPlayer::setPrint(string newPrint)     { m_sPrint = newPrint; }
void CPlayer::appendPrint(string newPrint)  { m_sPrint.append(newPrint); }
void CPlayer::setStatus(string status)      { m_status = status; }
void CPlayer::setFight(CFight* newFight)    { m_curFight = newFight; }

//*** FUNCTIONS *** // 

CPlayer::event CPlayer::callDialog(string sPlayerChoice)
{
    if(isdigit(sPlayerChoice[0]) == false) {
        appendPrint("Please choose an number\n");
        return std::make_pair("", "");
    }

    //Parse input
    size_t pos = m_status.find("/");
    string cur_id = m_status.substr(pos+1, m_status.length()-pos);
    string next_id = m_dialog->states[cur_id]->getOptions()[stoi(sPlayerChoice)].sTarget;

    //Call state
    callDialogState(next_id);

    //Return event
    event newEvent = std::make_pair(m_dialog->sName+"/"+next_id, "");
    return newEvent;
}

void CPlayer::callDialogState(string sDialogStateID)
{
    //Call state
    appendPrint(m_dialog->states[sDialogStateID]->callState());

    //Update status
    if(m_sPrint.find("Dialog ended") != string::npos)
        m_status = "standard";
    else
        m_status = "dialog/" + sDialogStateID;
}

CPlayer::event CPlayer::callFight(string sPlayerChoice) 
{
    return m_curFight->fightRound(sPlayerChoice);
}

void CPlayer::printInventory() {
    m_sPrint += m_sName + "'s Inventory: \n";
    for(auto it : m_inventory) 
        m_sPrint += "  " + std::to_string(it.second.size()) + "x " + it.second[0]->getName() +"\n";
}

void CPlayer::addItem(CItem* item) {
    if(item->getMoveable() == false) 
        m_sPrint += "I can't move this. No fucking way can I move this!\n";

    else {
        m_inventory[item->getID()].push_back(item);
        m_sPrint += "Item added to " + m_sName + "'s inventory.\n";
    }
}
        
string CPlayer::showStats() {
    string stats = "Name: " + m_sName + "\nID: " + m_sID + "\nStatus: " + m_status + "\n";
    stats += printAttacks();

    return stats;
}

