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

    //Initiazize world
    m_world = new CWorld();

    //Add eventhandler to eventmanager
    m_eventmanager["show"]      = {&CPlayer::h_show};
    m_eventmanager["lookIn"]    = {&CPlayer::h_lookIn};
    m_eventmanager["goTo"]      = {&CPlayer::h_goTo};
    m_eventmanager["talkTo"]    = {&CPlayer::h_startDialog};
    m_eventmanager["dialog"]    = {&CPlayer::h_callDialog};
    m_eventmanager["fight"]     = {&CPlayer::h_callFight};
    m_eventmanager["take"]      = {&CPlayer::h_take};
    m_eventmanager["use"]       = {&CPlayer::h_use};
    m_eventmanager["help"]      = {&CPlayer::h_help};
    m_eventmanager["error"]     = {&CPlayer::h_error};

    //Dialogs
    m_eventmanager["pissingManDialog/fuckoff"]   = {&CPlayer::h_pissingman_fuckoff};

    //Rooms
    m_eventmanager["goTo"].push_back(&CPlayer::h_firstZombieAttack);

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

string CPlayer::getObject(objectmap& mapObjects, string sIdentifier)
{
    for(auto it : mapObjects) {
        if(fuzzy::fuzzy_cmp(it.second, sIdentifier) <= 0.2) 
            return it.first;
    }
    return "";
}


// ***** ***** EVENTMANAGER FUNCTIONS ***** *****

void CPlayer::throw_event(event newEvent)
{
    if(m_eventmanager.count(newEvent.first) == 0) return;
        
    for(auto it : m_eventmanager[newEvent.first])
        (this->*it)(newEvent.second);
}


// ****************** EVENTHANDLER ********************** //

void CPlayer::h_show(string sIdentifier) {
    if(sIdentifier == "exits")
        m_sPrint += m_room->showExits();
    else if(sIdentifier == "chars")
        m_sPrint += m_room->showCharacters();
    else if(sIdentifier == "room")
        m_sPrint += m_room->showDescription(m_world->getCharacters());
    else if(sIdentifier == "items")
        m_sPrint += m_room->showItems();
    else if(sIdentifier == "details")
        m_sPrint += m_room->showDetails();
    else if(sIdentifier == "inventory")
        printInventory();
    else if(sIdentifier == "stats")
        m_sPrint += showStats();
}

void CPlayer::h_lookIn(string sIdentifier) {
    m_sPrint += m_room->look("in", sIdentifier);
}

void CPlayer::h_goTo(std::string sIdentifier) {

    //Get selected room
    string room = getObject(m_room->getExtits(), sIdentifier);

    //Check if room was found
    if(room == "") {
        m_sPrint += "Room/ exit not found";
        return;
    }

    //Print description and change players current room
    m_sPrint += m_world->getRooms()[room]->showEntryDescription(m_world->getCharacters());
    m_room = m_world->getRooms()[room];
}

void CPlayer::h_startDialog(string sIdentifier)
{
    //Get selected character
    string character = getObject(m_room->getCharacters(), sIdentifier);

    //Check if character was found
    if(character == "") {
        m_sPrint += "Characters not found";
        return;
    }

    //Update player status and call dialog state
    setDialog(m_world->getCharacters()[character]->getDialog());
    callDialogState("START");
}

void CPlayer::h_callDialog(string sIdentifier) {
    throw_event(callDialog(sIdentifier));
}

void CPlayer::h_callFight(string sIdentifier) {
    throw_event(callFight(sIdentifier));
}

void CPlayer::h_take(string sIdentifier) {
    if(m_room->getItem(sIdentifier) == NULL)
        m_sPrint += "Item not found.\n";
    else
        addItem(m_room->getItem(sIdentifier));
}

void CPlayer::h_use(string sIdentifier) {
    useItem(sIdentifier);
}

void CPlayer::h_help(string sIdentifier) {
    std::ifstream read("factory/help/help.txt");

    string str((std::istreambuf_iterator<char>(read)),
                 std::istreambuf_iterator<char>());
    m_sPrint += str;
}

void CPlayer::h_error(string sIdentifier) {
    m_sPrint += "This command is unkown. Type \"help\" to see possible command.\n";
}


// *** DIALOG HANDLER *** //
void CPlayer::h_pissingman_fuckoff(string sIdentifier) {
    m_world->getCharacters()["pissing_man"]->setDialog(m_world->dialogFactory("defaultDialog"));
}

// *** ROOM HANDLER *** //
void CPlayer::h_firstZombieAttack(string sIdentifier)
{
    //Get selected room
    if(m_room->getID() != "hospital_stairs")
        return;

    m_sPrint += "\n$";

    //Create fight
    CFight* fight = new CFight("First Fight", "A zombie comes running down the stairs and attacks you!", this, m_world->getCharacters()["hospital_zombie1"]);
    setFight(fight);
    setStatus("fight");
    fight->initializeFight();

    m_eventmanager["goTo"].erase(m_eventmanager["goTo"].begin()+1);
}


