#include "CGame.hpp"

void CGame::worldFactory()
{
    //Create rooms
    roomFactory();

    m_player.setRoom(m_rooms["compartment-a"]);

    //Add eventhandlers to eventmanager 
    m_eventmanager["showExits"] = {&CGame::showExits};
    m_eventmanager["showChars"] = {&CGame::showChars};
    m_eventmanager["showDesc"]  = {&CGame::showDesc};
    m_eventmanager["goTo"]      = {&CGame::goTo};
    m_eventmanager["talkTo"]    = {&CGame::startDialog};
    m_eventmanager["dialog"]    = {&CGame::callDialog};
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

void CGame::throw_event(std::pair<std::string, std::string> event)
{
    if(m_eventmanager.count(event.first) == 0) return;
        
    for(auto it : m_eventmanager[event.first])
        (this->*it)(event.first, event.second);
}

void CGame::showExits(std::string sType, std::string sIdentifier) {
    m_player.appendPrint("Exits: \n");
    size_t counter=1;
    for(auto it : m_player.getRoom()->getExtits()) {
        m_player.appendPrint(std::to_string(counter) + ": " + it.second + "\n");
        counter++;
    }
}

void CGame::showChars(std::string sType, std::string sIdentifier) {
    m_player.appendPrint("Characters: \n");
    size_t counter=1;
    for(auto it : m_player.getRoom()->getCharacters()) {
        m_player.appendPrint(std::to_string(counter) + ": " + it.second + "\n");
        counter++;
    }
}

void CGame::showDesc(std::string sType, std::string sIdentifier) {
    m_player.appendPrint(m_player.getRoom()->getDescription());
}

void CGame::goTo(std::string sType, std::string sIdentifier) {

    for(auto it : m_player.getRoom()->getExtits())
    {
        if(fuzzy::fuzzy_cmp(it.second, sIdentifier) <= 0.2)
        {
            m_player.appendPrint(m_rooms[it.first]->getEntry());
            m_player.appendPrint(m_rooms[it.first]->getDescription() + "\n");
            for(auto jt : m_rooms[it.first]->getCharacters())
                m_player.appendPrint(m_characters[jt.first]->getDescription());
            m_player.setRoom(m_rooms[it.first]);
            return;
        }
    }

    m_player.appendPrint("Room not found.\n");
}

void CGame::startDialog(std::string sType, std::string sIdentifier)
{
    dialog dia;

    //Get dialog
    for(auto it : m_player.getRoom()->getCharacters()) {
        if(fuzzy::fuzzy_cmp(it.second, sIdentifier) <= 0.2)
            dia = m_characters[it.first]->getDialog();
    }
    if(dia.size() == 0) {
        m_player.appendPrint("Character not found");
        return;
    }

    //Update player status
    m_player.setDialog(dia);
    
    //Call dialog state
    callDialogState("START");
}

void CGame::callDialog(std::string sType, std::string sIdentifier)
{
    dialog dia = m_player.getDialog();
    std::string status = m_player.getStatus();
    size_t pos = status.find("/");
    std::string cur_id  = status.substr(pos+1, status.length()-pos);
    std::cout << cur_id << "\n";
    std::string next_id = dia[cur_id]->getOptions()[stoi(sIdentifier)]->getTargetState();
    callDialogState(next_id);
}

void CGame::callDialogState(std::string dialogStateID)
{
    //Print first text
    m_player.appendPrint(m_player.getDialog()[dialogStateID]->getText()+"\n");

    if(m_player.getDialog()[dialogStateID]->getOptions().size() == 0)
    {
        m_player.appendPrint("Dialog enden.\n\n");
        m_player.setStatus("standard");
        return;
    }

    size_t counter = 1;
    for(auto it : m_player.getDialog()[dialogStateID]->getOptions())
    {
        m_player.appendPrint(std::to_string(counter) + ": " + it.second->getText() + "\n");
        counter++;
    }
    m_player.setStatus("dialog/" + dialogStateID);
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
