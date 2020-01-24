#include "CPlayer.hpp"

CPlayer::CPlayer(string sName,string sPassword, string sID, int hp, size_t strength, int gold, CRoom* room, attacks newAttacks)
{
    m_sName = sName;
    m_sPassword = sPassword;
    m_firstLogin = false;
    m_sID = sID;
    m_hp = hp;
    m_gold = gold;
    m_strength = strength;
    m_highness = 0;
    m_room = room;
    m_status = "standard";
    m_attacks = newAttacks;

    m_equipment["weapon"] = NULL;
    m_equipment["armor"]  = NULL;
    
    //Initiazize world
    m_world = new CWorld();

    //Add eventhandler to eventmanager
    m_contextStack.push_back( new CWorldContext(true, &CContext::worldParser));
    m_contextStack.push_back( new CStandardContext(false, &CContext::standardParser));
}

// *** GETTER *** // 
CRoom* CPlayer::getRoom()   { return m_room; }

string CPlayer::getPrint()  { 
    checkHighness();
    m_sPrint+="\n\n";
    return m_sPrint; 
}

string CPlayer::getStatus() { return m_status; };
bool CPlayer::getFirstLogin() { return m_firstLogin; };
CFight* CPlayer::getFight() { return m_curFight; };
size_t CPlayer::getHighness() { return m_highness; };
CPlayer::equipment& CPlayer::getEquipment()  { return m_equipment; }
CWorld* CPlayer::getWorld() { return m_world; }
std::deque<CContext*>& CPlayer::getContexts()   { return m_contextStack; }

// *** SETTER *** // 
void CPlayer::setRoom(CRoom* room)          { m_room = room; }
void CPlayer::setPrint(string newPrint)     { m_sPrint = newPrint; }
void CPlayer::appendPrint(string newPrint)  { m_sPrint.append(newPrint); }
void CPlayer::setStatus(string status)      { m_status = status; }
void CPlayer::setHighness(size_t highness)  { m_highness = highness; }



// *** *** FUNCTIONS *** *** // 


// *** Context-Stack ***
void CPlayer::newContext(CContext* context, size_t pos) {
    std::cout << "Added new context at: " << pos << std::endl;
    m_contextStack.insert(m_contextStack.begin()+pos, context);
}

void CPlayer::deleteContext(size_t pos)
{
    std::cout << "deleted context at: " << pos << std::endl;
    delete m_contextStack[pos];
    m_contextStack.erase(m_contextStack.begin()+pos);
}

// *** Fight *** //
void CPlayer::setFight(CFight* newFight) { 
    m_curFight = newFight;
    newContext(new CFightContext(false, &CContext::fightParser), 1);
    m_curFight->initializeFight();
}

void CPlayer::endFight() {
    delete m_curFight;
    deleteContext(1);
    m_sPrint += "Fight ended.\n";
}



// *** Item and inventory *** //
void CPlayer::printInventory() {
    m_sPrint += m_sName + "'s Inventory: \n";

    string sEquipment = "Equipment: ";
    string sConsume = "Food and Drinks: ";
    string sOthers = "Others: ";
    for(auto it : m_inventory) {
        if(it.second[0]->getAttribute<string>("type").find("equipe") != string::npos)
            sEquipment += std::to_string(it.second.size()) + "x " + it.second[0]->getName() + ", ";

        else if(it.second[0]->getAttribute<string>("type").find("consume") != string::npos)
            sConsume += std::to_string(it.second.size()) + "x " + it.second[0]->getName() + ", ";

        else 
            sOthers += std::to_string(it.second.size()) + "x " + it.second[0]->getName() + ", ";
    }
    m_sPrint += sEquipment +"\n"+ sConsume +"\n" + sOthers + "\n";
}


void CPlayer::printEquiped() {
    for(auto it : m_equipment) {
        if(it.second != NULL)
            m_sPrint += it.first + ": " + it.second->getName() + "\n"; 
        else
            m_sPrint += it.first + ": empty handed as it seems.\n";
    }
}

void CPlayer::addItem(CItem* item) {
    m_inventory[item->getAttribute<string>("name")].push_back(item);
    m_sPrint += item->getAttribute<string>("name") + " added to " + m_sName + "'s inventory.\n";
    m_room->getItems().erase(item->getAttribute<string>("id"));
}

void CPlayer::removeItem(string sItemName) {
    m_inventory[sItemName].pop_back();
    if(m_inventory[sItemName].size() == 0)
        m_inventory.erase(sItemName);
}

CItem* CPlayer::getItem(string sName)
{
    for(auto it : m_inventory) {
        if(fuzzy::fuzzy_cmp(it.second[0]->getName(), sName) <= 0.2) 
            return it.second[0];
    }
    m_sPrint += "Item not in inventory! (use \"show inventory\" to see your items.)\n";
    return NULL;
}

CItem* CPlayer::getItem_byID(string id)
{
    for(auto it : m_inventory) {
        if(it.second[0]->getID() == id)
            return it.second[0];
    }
    return NULL;
}

void CPlayer::equipeItem(CItem* item, string sType)
{
    if(m_equipment[sType] == NULL)
    {
        m_sPrint += "You equiped " + sType + ": " + item->getName() + ".\n";
        string sAttack = item->getAttribute<string>("attack");
        if(sAttack != "") {
            m_attacks[sAttack] = m_world->getAttacks()[sAttack];
            m_sPrint += "New attack: \"" + m_attacks[sAttack]->getName() + "\" added to arracks.\n";
        }
        m_equipment[sType] = item;
    }

    else if(m_equipment[sType]->getID() == item->getID())
        m_sPrint+=sType + " already equiped.\n";
    else
    {
        m_sPrint+="Already a " + sType + " equipt. Want to change? (yes/no)\n";
        CChoiceContext* context = new CChoiceContext(false, &CContext::choiceParser, item->getID());
        context->add_listener("choose", &CContext::h_choose_equipe);
        newContext(context, 1);
    }
}

void CPlayer::dequipeItem(string sType) {
    if(m_equipment.count(sType) == 0)
        m_sPrint += "Nothing to dequipe.\n";
    else if(m_equipment[sType] == NULL)
        m_sPrint += "Nothing to dequipe.\n";
    else {
        m_sPrint += "Dequiped " + sType + " " + m_equipment[sType]->getName() + ".\n";
        string sAttack = m_equipment[sType]->getAttribute<string>("attack");
        if(sAttack != "")
            m_attacks.erase(sAttack);
        m_equipment[sType] = NULL;
    }
}


// *** Stats *** //
string CPlayer::showStats() {
    string stats = "Name: " + m_sName 
        + "\nHP: " + std::to_string(m_hp) 
        + "\nStrength: " + std::to_string(m_strength)
        + "\nHighness: " + std::to_string(m_highness) 
        + "\n" 
        + printAttacks();

    return stats;
}


// *** Others *** // 
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


string CPlayer::doLogin(string sName, string sPassword)
{
    if(sName == m_sName && sPassword == m_sPassword) return m_sID;
    else return "";
}

string CPlayer::getObject(objectmap& mapObjects, string sIdentifier)
{
    for(auto it : mapObjects) {
        if(fuzzy::fuzzy_cmp(it.second, sIdentifier) <= 0.2) 
            return it.first;
    }
    return "";
}


// ***** ***** EVENTMANAGER FUNCTIONS ***** *****

void CPlayer::throw_event(string sInput)
{
    checkTimeEvents();
    for(size_t i=0; i<m_contextStack.size(); i++)
    {
        m_contextStack[i]->throw_event(sInput, this);
        if(m_contextStack[i]->getPermeable() == false)
            break;
    }
}


// ***** ***** TIME EVENTS ****** *****
bool CPlayer::checkEventExists(string sType)
{
    return m_timeEventes.count(sType) > 0;
}
void CPlayer::addTimeEvent(string sType, double duration, void (CPlayer::*func)())
{
    auto start = std::chrono::system_clock::now();
    m_timeEventes[sType].push_back(std::make_tuple(start, duration*60, func));
}

void CPlayer::checkTimeEvents()
{
    std::list<std::pair<std::string, size_t>> lExecute;

    //Collect element to be executed
    auto end = std::chrono::system_clock::now();
    for(auto it : m_timeEventes)
    {
        std::cout << "ititializing... \n";
        size_t counter=0;
        for(auto jt : m_timeEventes[it.first]) {
            std::chrono::duration<double> diff = end - std::get<0>(jt);
            if(diff.count() >= std::get<1>(jt))
                lExecute.push_back(std::make_pair(it.first, counter));
        }
    }

    std::cout << "initializes execute. \n";

    //Execute events and delete afterwards
    for(auto it : lExecute) {
        std::cout << "Calling and deleting: " << it.first << "/" << it.second << std::endl;
        (this->*std::get<2>(m_timeEventes[it.first][it.second]))();
        m_timeEventes[it.first].erase(m_timeEventes[it.first].begin() + it.second);
        if(m_timeEventes[it.first].size() == 0)
            m_timeEventes.erase(it.first);
    }

}

// Time handler
void CPlayer::t_highness()
{
    if(m_highness==0)
        return;
    m_sPrint += "Time always comes to give you a hand; Things begin to become clearer again. Highness decreased by 1.\n";
    m_highness--;

    if(m_highness>0)
        addTimeEvent("highness", 0.25, &CPlayer::t_highness);
}

