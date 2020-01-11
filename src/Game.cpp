#include "CGame.hpp"

namespace fs = std::filesystem;

CGame::CGame() {
    worldFactory();
}

// ****************** FACTORYS ********************** //
void CGame::worldFactory()
{
    //Initialize dialog-functions
    CDState::initializeFunctions();

    //Create rooms
    roomFactory();

    //Create attacks
    attackFactory();

    //Create players
    playerFactory();
    std::cout << "Finished parsing!\n";

    //Add eventhandlers to eventmanager 
    m_eventmanager["show"]      = {&CGame::show};
    m_eventmanager["goTo"]      = {&CGame::goTo};
    m_eventmanager["talkTo"]    = {&CGame::startDialog};
    m_eventmanager["dialog"]    = {&CGame::callDialog};
    m_eventmanager["error"]     = {&CGame::error};

    m_eventmanager["pissingManDialog/fuckoff"]   = {&CGame::pissingman_fuckoff};
}

void CGame::roomFactory()
{
    for(auto& p : fs::directory_iterator("factory/jsons/rooms"))
        roomFactory(p.path());
}

void CGame::roomFactory(string sPath)
{
    //Read json creating all rooms
    std::ifstream read(sPath);
    nlohmann::json j_rooms;
    read >> j_rooms;
    read.close();
    
    for(auto j_room : j_rooms )
    {
        std::cout << "Parsing " << j_room["name"] << "...\n";
        //Parse characters 
        objectmap mapChars = characterFactory(j_room["characters"]);

        //Create new room
        m_rooms[j_room["id"]] = new CRoom(j_room["name"], j_room["description"], j_room.value("entry", ""), j_room["exits"], mapChars); 
    }
}

CGame::objectmap CGame::characterFactory(nlohmann::json j_characters)
{
    objectmap mapChars;
    for(auto j_char : j_characters)
    {
        std::cout << "Parsing " << j_char["name"] << "\n";

        //Create dialog 
        SDialog* newDialog = new SDialog;
        if(j_char.count("dialog") > 0)
            newDialog = dialogFactory(j_char["dialog"]); 
        else
            newDialog = dialogFactory("defaultDialog");

        //Create attacks
        objectmap attacks;
        if(j_char.count("attacks") > 0) attacks = j_char["attacks"].get<objectmap>();

        //Create character and add to maps
        m_characters[j_char["id"]] = new CCharacter(j_char["name"],j_char.value("description",""), newDialog, attacks);
        mapChars[j_char["id"]] = j_char["name"];
    }

    return mapChars;
}

void CGame::attackFactory()
{
    for(auto& p : fs::directory_iterator("factory/jsons/attacks"))
        attackFactory(p.path());
}

void CGame::attackFactory(std::string sPath) {
    //Read json creating all rooms
    std::ifstream read(sPath);
    nlohmann::json j_attacks;
    read >> j_attacks;
    read.close();

    for(auto j_attack : j_attacks) 
        m_attacks[j_attack["id"]] = new CAttack(j_attack["name"], j_attack["description"], j_attack["output"], j_attack["power"]);
}


SDialog* CGame::dialogFactory(string sPath)
{
    //Read json creating all rooms
    std::ifstream read("factory/jsons/dialogs/"+sPath+".json");
    nlohmann::json j_states;
    read >> j_states;
    read.close();

    //Create new dialog
    map<string, CDState*> mapStates;
    struct SDialog* newDialog = new SDialog();

    for(auto j_state : j_states)
    {
        // *** parse options *** //
        map<int, SDOption> options;
        if(j_state.count("options") != 0)
        {
            for(auto j_opt : j_state["options"])
                options[j_opt["id"]] = {j_opt["text"], j_opt["targetstate"]};
        }

        // *** parse state *** //

        //Parse alternative texts
        vector<string> altTexts;
        if(j_state.count("altTexts") > 0) 
            altTexts = j_state["altTexts"].get<vector<string>>();

        //Create state
        mapStates[j_state["id"]] = new CDState(j_state["text"], j_state.value("function", "standard"), altTexts, options, newDialog);
    }

    //Update dialog values and return
    newDialog->sName = sPath;
    newDialog->states= mapStates;
    return newDialog;
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
        objectmap attacks;
        if(j_player.count("attacks") > 0) attacks = j_player["attacks"].get<objectmap>();


        m_players[j_player["id"]] = new CPlayer(j_player["name"], j_player["id"], m_rooms[j_player["room"]], attacks);
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
        m_curPlayer->appendPrint(m_curPlayer->getRoom()->showDescription(m_characters));
    else if(sIdentifier == "stats")
        m_curPlayer->appendPrint(m_curPlayer->showStats(m_attacks));
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
    m_curPlayer->appendPrint(m_rooms[room]->showEntryDescription(m_characters));
    m_curPlayer->setRoom(m_rooms[room]);
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
    m_curPlayer->setDialog(m_characters[character]->getDialog());
    m_curPlayer->callDialogState("START");
}

void CGame::callDialog(string sIdentifier) {
    event newEvent = std::make_pair(m_curPlayer->callDialog(sIdentifier), "");
    throw_event(newEvent);
}

void CGame::error(string sIdentifier) {
    m_curPlayer->appendPrint("This command is unkown.\n");
}


// *** DIALOG HANDLER *** //
void CGame::pissingman_fuckoff(string sIdentifier) {
    m_characters["pissing_man"]->setDialog(dialogFactory("defaultDialog"));
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
