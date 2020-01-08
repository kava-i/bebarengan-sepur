#include "CGame.hpp"

// ****************** FACTORYS ********************** //
void CGame::worldFactory()
{
    //Create rooms
    roomFactory();

    m_player.setRoom(m_rooms["compartment-a"]);

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
        //Create dialog 
        dialog newDialog;
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

std::map<std::string, CDState*> CGame::dialogFactory(std::string sPath)
{
    //Read json creating all rooms
    std::ifstream read("factory/"+sPath+".json");
    nlohmann::json j_states;
    read >> j_states;
    read.close();

    dialog newDialog;
    for(auto j_state : j_states)
    {
        // *** parse options *** //
        std::map<size_t, CDOption*> options;
        if(j_state.count("options") != 0)
        {
            for(auto j_opt : j_state["options"])
                options[j_opt["id"]] = new CDOption (j_opt["id"], j_opt["text"], j_opt["targetstate"], j_opt.value("active", false));
        }

        // *** parse state *** //
        newDialog[j_state["id"]] = new CDState(j_state["id"], j_state["text"], options);
    }

    return newDialog;
}


// ****************** FUNCTIONS CALLER ********************** //

std::string CGame::play(std::string sInput)
{
    //Create parser
    CCommandParser parser;
    m_player.setPrint("");

    //Parse command and create event
    std::pair<std::string, std::string> event = parser.parse(sInput, m_player.getStatus());

    //Throw event and delete afterwards
    throw_event(event);

    return m_player.getPrint(); 
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
        m_player.appendPrint(m_player.getRoom()->showExits());
    else if(sIdentifier == "chars")
        m_player.appendPrint(m_player.getRoom()->showCharacters());
    else if(sIdentifier == "room")
        m_player.appendPrint(m_player.getRoom()->showDescription(m_characters));
}

void CGame::goTo(std::string sIdentifier) {

    //Get selected room
    std::string room = getObject(m_player.getRoom()->getExtits(), sIdentifier);

    //Check if room was found
    if(room == "") {
        m_player.appendPrint("Room/ exit not found");
        return;
    }

    //Print description and change players current room
    m_player.appendPrint(m_rooms[room]->showEntryDescription(m_characters));
    m_player.setRoom(m_rooms[room]);
}

void CGame::startDialog(std::string sIdentifier)
{
    //Get selected character
    std::string character = getObject(m_player.getRoom()->getCharacters(), sIdentifier);

    //Check if character was found
    if(character == "")
    {
        m_player.appendPrint("Characters not found");
        return;
    }

    //Update player status and call dialog state
    m_player.setDialog(m_characters[character]->getDialog());
    m_player.callDialogState("START");
}

void CGame::callDialog(std::string sIdentifier) {
    m_player.callDialog(sIdentifier);
}

void CGame::error(std::string sIdentifier) {
    m_player.appendPrint("This command is unkown.\n");
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
