#include "CGame.hpp"


CGame::CGame() {
    worldFactory();
}

// ****************** FACTORYS ********************** //
void CGame::worldFactory()
{
    //Create rooms
    CDState::initializeFunctions();
    roomFactory();

    //Create players
    playerFactory();

    //Add eventhandlers to eventmanager 
    m_eventmanager["show"]      = {&CGame::show};
    m_eventmanager["goTo"]      = {&CGame::goTo};
    m_eventmanager["talkTo"]    = {&CGame::startDialog};
    m_eventmanager["dialog"]    = {&CGame::callDialog};
    m_eventmanager["error"]     = {&CGame::error};
}

void CGame::roomFactory()
{
    //Read json creating all rooms
    std::ifstream read("factory/rooms.json");
    nlohmann::json j_rooms;
    read >> j_rooms;
    read.close();
    
    for(auto j_room : j_rooms )
    {
        std::cout << "Parsing " << j_room["name"] << "...\n";
        //Parse characters 
        objectmap mapChars = characterFactory(j_room["characters"]);

        //Create new room
        CRoom* room = new CRoom(j_room["name"], j_room["description"], j_room.value("entry", ""), j_room["exits"], mapChars); 
        m_rooms[j_room["id"]] = room;
    }
}

std::map<std::string, std::string> CGame::characterFactory(nlohmann::json j_characters)
{
    objectmap mapChars;
    for(auto j_char : j_characters)
    {
        std::cout << "Parsing " << j_char["name"] << "...\n";
        //Create dialog 
        dialog* newDialog = new dialog;
        if(j_char.count("dialog") > 0)
            newDialog = dialogFactory(j_char["dialog"]); 
        else
            newDialog = dialogFactory("defaultDialog");

        CCharacter* character = new CCharacter(j_char["name"],j_char.value("description",""), newDialog);
        m_characters[j_char["id"]] = character;
        mapChars[j_char["id"]] = j_char["name"];
    }

    return mapChars;
}

std::map<std::string, CDState*>* CGame::dialogFactory(std::string sPath)
{
    //Read json creating all rooms
    std::ifstream read("factory/"+sPath+".json");
    nlohmann::json j_states;
    read >> j_states;
    read.close();

    std::cout << "Parsing dialog...\n";
    dialog* newDialog = new dialog;
    for(auto j_state : j_states)
    {
        // *** parse options *** //
        std::map<int, CDOption*> options;
        if(j_state.count("options") != 0)
        {
            for(auto j_opt : j_state["options"])
                options[j_opt["id"]] = new CDOption (j_opt["id"], j_opt["text"], j_opt["targetstate"], j_opt.value("active", false));
        }

        // *** parse state *** //
        (*newDialog)[j_state["id"]] = new CDState(j_state["id"], j_state["text"], j_state.value("function", "standard"), options, newDialog);
    }

    return newDialog;
}

void CGame::playerFactory()
{
    //Read json creating all rooms
    std::ifstream read("factory/players.json");
    nlohmann::json j_players;
    read >> j_players;
    read.close();

    for(auto j_player : j_players)
    {
        CPlayer* player = new CPlayer(j_player["name"], j_player["id"], m_rooms[j_player["room"]]);
        m_players[j_player["id"]] = player;
    }
}



// ****************** FUNCTIONS CALLER ********************** //

std::string CGame::play(std::string sInput, std::string sPlayerID)
{
    //Create parser
    CCommandParser parser;

    //Create player
    m_curPlayer = m_players[sPlayerID];
    m_curPlayer->setPrint("");

    //Parse command and create event
    std::pair<std::string, std::string> event = parser.parse(sInput, m_curPlayer->getStatus());

    //Throw event and delete afterwards
    throw_event(event);

    return m_curPlayer->getPrint(); 
}


// ****************** EVENTMANAGER ********************** //

void CGame::throw_event(std::pair<std::string, std::string> event)
{
    if(m_eventmanager.count(event.first) == 0) return;
        
    for(auto it : m_eventmanager[event.first])
        (this->*it)(event.second);
}


// ****************** EVENTHANDLER ********************** //

void CGame::show(std::string sIdentifier) {
    if(sIdentifier == "exits")
        m_curPlayer->appendPrint(m_curPlayer->getRoom()->showExits());
    else if(sIdentifier == "chars")
        m_curPlayer->appendPrint(m_curPlayer->getRoom()->showCharacters());
    else if(sIdentifier == "room")
        m_curPlayer->appendPrint(m_curPlayer->getRoom()->showDescription(m_characters));
    else if(sIdentifier == "stats")
        m_curPlayer->appendPrint(m_curPlayer->showStats());
}

void CGame::goTo(std::string sIdentifier) {

    //Get selected room
    std::string room = getObject(m_curPlayer->getRoom()->getExtits(), sIdentifier);

    //Check if room was found
    if(room == "") {
        m_curPlayer->appendPrint("Room/ exit not found");
        return;
    }

    //Print description and change players current room
    m_curPlayer->appendPrint(m_rooms[room]->showEntryDescription(m_characters));
    m_curPlayer->setRoom(m_rooms[room]);
}

void CGame::startDialog(std::string sIdentifier)
{
    //Get selected character
    std::string character = getObject(m_curPlayer->getRoom()->getCharacters(), sIdentifier);

    //Check if character was found
    if(character == "")
    {
        m_curPlayer->appendPrint("Characters not found");
        return;
    }

    //Update player status and call dialog state
    m_curPlayer->setDialog(m_characters[character]->getDialog());
    m_curPlayer->callDialogState("START");
}

void CGame::callDialog(std::string sIdentifier) {
    m_curPlayer->callDialog(sIdentifier);
}

void CGame::error(std::string sIdentifier) {
    m_curPlayer->appendPrint("This command is unkown.\n");
}


// ****************** VARIOUS FUNCTIONS ********************** //

std::string CGame::getObject(objectmap& mapObjects, std::string sIdentifier)
{
    for(auto it : mapObjects) {
    if(fuzzy::fuzzy_cmp(it.second, sIdentifier) <= 0.2) 
        return it.first;
    }
    return "";
}

/*
void CGame::toJson(std::string filename)
{
    //Convert yaml to json using python
	Py_Initialize();
	FILE* fp = _Py_fopen(filename, "r");
	PyRun_SimpleFile(fp, filename);

	Py_Finalize();
}
*/ 
