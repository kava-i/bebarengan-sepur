#include "CPlayer.hpp"

CPlayer::CPlayer(string sName, string sID, int hp, size_t strength, CRoom* room, attacks newAttacks)
{
    m_sName = sName;
    m_sID = sID;
    m_hp = hp;
    m_strength = strength;
    m_highness = 0;
    m_room = room;
    m_status = "standard";
    m_attacks = newAttacks;
}

// *** GETTER *** // 
CRoom* CPlayer::getRoom()   { 
    return m_room; 
}

string CPlayer::getPrint()  { 
    checkHighness();
    m_sPrint+="\n\n";
    return m_sPrint; 
}

string CPlayer::getStatus() { 
    return m_status; 
};

CFight* CPlayer::getFight() { 
    return m_curFight;
};

size_t CPlayer::getHighness() { 
    return m_highness; 
};

// *** SETTER *** // 
void CPlayer::setRoom(CRoom* room)          { m_room = room; }
void CPlayer::setPrint(string newPrint)     { m_sPrint = newPrint; }
void CPlayer::appendPrint(string newPrint)  { m_sPrint.append(newPrint); }
void CPlayer::setStatus(string status)      { m_status = status; }
void CPlayer::setFight(CFight* newFight)    { m_curFight = newFight; }
void CPlayer::setHighness(size_t highness)  { m_highness = highness; }

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

    string m_sEquipment = "Equipment: ";
    string m_sConsume = "Food and Drinks: ";
    for(auto it : m_inventory) {
        if(it.second[0]->getAttribute<string>("type").find("equipe") != string::npos)
            m_sEquipment += std::to_string(it.second.size()) + "x " + it.second[0]->getAttribute<string>("name") +", ";
            
        else if(it.second[0]->getAttribute<string>("type").find("consume") != string::npos)
            m_sConsume += std::to_string(it.second.size()) + "x " + it.second[0]->getAttribute<string>("name") +", ";

    }
    m_sPrint += m_sEquipment +"\n"+ m_sConsume +"\n";
}

void CPlayer::addItem(CItem* item) {
    m_inventory[item->getAttribute<string>("name")].push_back(item);
    m_sPrint += item->getAttribute<string>("name") + " added to " + m_sName + "'s inventory.\n";
    m_room->getItems().erase(item->getAttribute<string>("id"));
}

void CPlayer::useItem(string sPlayerChoice) {
    for(auto it : m_inventory) {
        if(fuzzy::fuzzy_cmp(it.second[0]->getAttribute<string>("name"), sPlayerChoice) <= 0.2) {
            m_sPrint += it.second[0]->callFunction(this);
            return;
         }
    }

    m_sPrint += "Item not in inventory.\n";
}       

void CPlayer::removeItem(string sItemName) {
    m_inventory[sItemName].pop_back();
    if(m_inventory[sItemName].size() == 0)
        m_inventory.erase(sItemName);
}

string CPlayer::showStats() {
    string stats = "Name: " + m_sName 
        + "\nHP: " + std::to_string(m_hp) 
        + "\nStrength: " + std::to_string(m_strength)
        + "\nHighness: " + std::to_string(m_highness) 
        + "\n" 
        + printAttacks();

    return stats;
}

void CPlayer::checkHighness()
{
    if(m_highness==0)
        return; 

    srand(time(NULL));
    std::vector<string> words = func::split(m_sPrint, " ");

    size_t limit = (11-m_highness)/2;

    size_t counter = 0;
    for(auto& word : words)
    {
        if(counter%(limit)!= 0) {
            counter++;
            continue;
        }

        for(size_t i=0; i<word.size(); i++) {

            if(i%(limit) != 0 || isalpha(word[i]) == false)
                continue;
            size_t num = rand() % word.size()-1;
            if(!isalpha(word[num]))
                continue;

            char x = word[i];
            word[i] = word[num];
            word[num] = x;
        }
        counter++;
    }

    m_sPrint="";
    for(auto word : words)
        m_sPrint+=word + " ";
}

