#include "CGame.hpp"

void CGame::worldFactory()
{
    //Create rooms
    roomFactory();

    m_player.setRoom(m_rooms["compartment-a"]);

    //Add eventhandlers to eventmanager 
    m_eventmanager["showExits"] = {&CGame::showExits};
    m_eventmanager["showChars"] = {&CGame::showChars};
    m_eventmanager["goTo"]      = {&CGame::goTo};
    m_eventmanager["talkTZoz"]      = {&CGame::startDialog};
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
        CRoom* room = new CRoom(j_room["name"], j_room["description"], j_room["exits"], mapChars); 
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

        CCharacter* character = new CCharacter(j_char["name"], newDialog);
        m_characters[j_char["id"]] = character;
        mapChars[j_char["id"]] = j_char["name"];
    }

    return mapChars;
}

std::map<std::string, CDState*> CGame::dialogFactory(std::string sPath)
{
    std::cout << "Parsing dialog...\n";

    //Read json creating all rooms
    std::ifstream read("factory/"+sPath+".json");
    nlohmann::json j_states;
    read >> j_states;
    read.close();

    dialog newDialog;
    for(auto j_state : j_states)
    {
        // ** PARSE OPTIONS ** //
        std::map<size_t, CDOption*> options;
        if(j_states.count("options") != 0)
        {
            //Parse characters 
            for(auto j_option : j_state["options"])
            {
                CDOption* option = new CDOption(j_option["id"], j_option["text"], j_option["targetstate"], j_option.value("active", false));
                options[j_option["id"]] = option;
             }
        }

        // ** PARSE STATE ** //
        CDState* state = new CDState(j_state["id"], j_state["text"], options);

        newDialog[j_state["id"]] = state;
    }

    return newDialog;
}


std::string CGame::play(std::string sInput)
{
    //Create parser
    CCommandParser parser;
    m_player.setPrint("");

    //Parse command and create event
    std::pair<std::string, std::string> event = parser.parseCommand(sInput);

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
void CGame::goTo(std::string sType, std::string sIdentifier) {
    for(auto it : m_player.getRoom()->getExtits())
    {
        if(it.second == sIdentifier)
        {
            m_player.appendPrint(m_rooms[it.first]->getDescription() + "\n");
            m_player.setRoom(m_rooms[it.first]);
            return;
        }
    }

    m_player.appendPrint("Room not found.\n");
}

void CGame::startDialog(std::string sType, std::string sIdentifier)
{
    if(m_player.getRoom()->getCharacters().count(sIdentifier) == 0)
    {
        m_player.appendPrint("Character not found");
        return;
    }
    
    dialog dia = m_characters[m_player.getRoom()->getCharacters()[sIdentifier]]->getDialog();
    m_player.appendPrint(dia["START"]->getText());

    size_t counter = 0;
    for(auto it : dia["START"]->getOptions())
    {
        m_player.appendPrint(std::to_string(counter) + ": " + it.second->getText() + "\n");
        counter++;
    }
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
