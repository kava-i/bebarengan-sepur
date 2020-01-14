#include "CGame.hpp"


CGame::CGame() {
    m_world = new CWorld();

    //Create players
    playerFactory();
    std::cout << "Finished parsing!\n";

    //Add eventhandlers to eventmanager 
    m_eventmanager["show"]      = {&CGame::show};
    m_eventmanager["lookIn"]    = {&CGame::lookIn};
    m_eventmanager["goTo"]      = {&CGame::goTo};
    m_eventmanager["talkTo"]    = {&CGame::startDialog};
    m_eventmanager["dialog"]    = {&CGame::callDialog};
    m_eventmanager["fight"]     = {&CGame::callFight};
    m_eventmanager["take"]      = {&CGame::take};
    m_eventmanager["use"]       = {&CGame::use};
    m_eventmanager["help"]       = {&CGame::help};
    m_eventmanager["error"]     = {&CGame::error};

    //Dialogs
    m_eventmanager["pissingManDialog/fuckoff"]   = {&CGame::pissingman_fuckoff};

    //Rooms
    m_eventmanager["goTo"].push_back(&CGame::firstZombieAttack);
}

void CGame::playerFactory()
{
    std::cout << "Parsing players... \n";

    //Read json creating all rooms
    std::ifstream read("factory/jsons/players/players.json");
    nlohmann::json j_players;
    read >> j_players;
    read.close();

    for(auto j_player : j_players) {

        //Create attacks
        map<string, CAttack*> attacks = m_world->parsePersonAttacks(j_player);

        //Create player
        m_players[j_player["id"]] = new CPlayer(j_player["name"], j_player["id"], j_player.value("hp", 40), j_player.value("strength", 8), m_world->getRooms()[j_player["room"]], attacks);
    }
}



// ****************** FUNCTIONS CALLER ********************** //

string CGame::play(string sInput, string sPlayerID)
{
    //Create parser
    CCommandParser parser;

    //Create player
    m_curPlayer = m_players[sPlayerID];
    m_curPlayer->setPrint("");

    //Parse command and create event
    event newEvent = parser.parse(sInput, m_curPlayer->getStatus());

    //Throw event and delete afterwards
    throw_event(newEvent);

    return m_curPlayer->getPrint(); 
}


// ****************** EVENTMANAGER ********************** //

void CGame::throw_event(event newEvent)
{
    if(m_eventmanager.count(newEvent.first) == 0) return;
        
    for(auto it : m_eventmanager[newEvent.first])
        (this->*it)(newEvent.second);
}


// ****************** EVENTHANDLER ********************** //

void CGame::show(string sIdentifier) {
    if(sIdentifier == "exits")
        m_curPlayer->appendPrint(m_curPlayer->getRoom()->showExits());
    else if(sIdentifier == "chars")
        m_curPlayer->appendPrint(m_curPlayer->getRoom()->showCharacters());
    else if(sIdentifier == "room")
        m_curPlayer->appendPrint(m_curPlayer->getRoom()->showDescription(m_world->getCharacters()));
    else if(sIdentifier == "items")
        m_curPlayer->appendPrint(m_curPlayer->getRoom()->showItems());
    else if(sIdentifier == "details")
        m_curPlayer->appendPrint(m_curPlayer->getRoom()->showDetails());
    else if(sIdentifier == "inventory")
        m_curPlayer->printInventory();
    else if(sIdentifier == "stats")
        m_curPlayer->appendPrint(m_curPlayer->showStats());
}

void CGame::lookIn(string sIdentifier) {
    m_curPlayer->appendPrint(m_curPlayer->getRoom()->look("in", sIdentifier));
}

void CGame::goTo(std::string sIdentifier) {

    //Get selected room
    string room = getObject(m_curPlayer->getRoom()->getExtits(), sIdentifier);

    //Check if room was found
    if(room == "") {
        m_curPlayer->appendPrint("Room/ exit not found");
        return;
    }

    //Print description and change players current room
    m_curPlayer->appendPrint(m_world->getRooms()[room]->showEntryDescription(m_world->getCharacters()));
    m_curPlayer->setRoom(m_world->getRooms()[room]);
}

void CGame::startDialog(string sIdentifier)
{
    //Get selected character
    string character = getObject(m_curPlayer->getRoom()->getCharacters(), sIdentifier);

    //Check if character was found
    if(character == "") {
        m_curPlayer->appendPrint("Characters not found");
        return;
    }

    //Update player status and call dialog state
    m_curPlayer->setDialog(m_world->getCharacters()[character]->getDialog());
    m_curPlayer->callDialogState("START");
}

void CGame::callDialog(string sIdentifier) {
    throw_event(m_curPlayer->callDialog(sIdentifier));
}

void CGame::callFight(string sIdentifier) {
    throw_event(m_curPlayer->callFight(sIdentifier));
}

void CGame::take(string sIdentifier) {
    CItem* item = m_curPlayer->getRoom()->getItem(sIdentifier);
    if(item == NULL){
        m_curPlayer->appendPrint("Item not found.\n");
        return;
    }
    m_curPlayer->addItem(item);
}

void CGame::use(string sIdentifier) {
    m_curPlayer->useItem(sIdentifier);
}

void CGame::help(string sIdentifier) {
    std::ifstream read("factory/help/help.txt");

    string str((std::istreambuf_iterator<char>(read)),
                 std::istreambuf_iterator<char>());

    m_curPlayer->appendPrint(str);
}

void CGame::error(string sIdentifier) {
    m_curPlayer->appendPrint("This command is unkown. Type \"help\" to see possible command.\n");
}


// *** DIALOG HANDLER *** //
void CGame::pissingman_fuckoff(string sIdentifier) {
    m_world->getCharacters()["pissing_man"]->setDialog(m_world->dialogFactory("defaultDialog"));
}

// *** ROOM HANDLER *** //
void CGame::firstZombieAttack(string sIdentifier)
{
    //Get selected room
    if(m_curPlayer->getRoom()->getID() != "hospital_stairs")
        return;

    m_curPlayer->appendPrint("\n$"); 

    //Create fight
    CFight* fight = new CFight("First Fight", "A zombie comes running down the stairs and attacks you!", m_curPlayer, m_world->getCharacters()["hospital_zombie1"]);
    m_curPlayer->setFight(fight);
    m_curPlayer->setStatus("fight");
    fight->initializeFight();

    m_eventmanager["goTo"].erase(m_eventmanager["goTo"].begin()+1);
}


// ****************** VARIOUS FUNCTIONS ********************** //

string CGame::getObject(objectmap& mapObjects, string sIdentifier)
{
    for(auto it : mapObjects) {
        if(fuzzy::fuzzy_cmp(it.second, sIdentifier) <= 0.2) 
            return it.first;
    }
    return "";
}

/*
void CGame::toJson(string filename)
{
    //Convert yaml to json using python
	Py_Initialize();
	FILE* fp = _Py_fopen(filename, "r");
	PyRun_SimpleFile(fp, filename);

	Py_Finalize();
}
*/ 


