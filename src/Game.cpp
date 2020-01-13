#include "CGame.hpp"

namespace fs = std::filesystem;

CGame::CGame() {
    worldFactory();
}

// ****************** FACTORYS ********************** //
void CGame::worldFactory()
{
    //Initialize functions
    CDState::initializeFunctions();
    CItem::initializeFunctions();

    //Create attacks
    attackFactory();

    //Create rooms
    roomFactory();

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
    m_eventmanager["error"]     = {&CGame::error};

    //Dialogs
    m_eventmanager["pissingManDialog/fuckoff"]   = {&CGame::pissingman_fuckoff};

    //Rooms
    m_eventmanager["goTo"].push_back(&CGame::firstZombieAttack);
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
        //Parse characters 
        objectmap mapChars = characterFactory(j_room["characters"]);

        //Parse items
        map<string, CItem*> mapItems = itemFactory(j_room);

        //Parse details
        map<string, CDetail*> mapDetails = detailFactory(j_room);

        //Create new room
        m_rooms[j_room["id"]] = new CRoom(j_room["name"], j_room["id"], j_room["description"], j_room.value("entry", ""), j_room["exits"], mapChars, mapItems, mapDetails);
    }
}

map<string, CDetail*> CGame::detailFactory(nlohmann::json j_room)
{
    map<string, CDetail*> mapDetails;
    if(j_room.count("details") == 0)
        return mapDetails;

    for(auto j_detail : j_room["details"])
    {
        objectmap characters;
        if(j_detail.count("characters") > 0) 
            characters = j_detail["characters"].get<objectmap>();
        objectmap items;
        if(j_detail.count("items") > 0) 
            items = j_detail["items"].get<objectmap>();

        mapDetails[j_detail["id"]] = new CDetail(j_detail["name"], j_detail["id"], j_detail["description"], j_detail["look"], characters, items);
    }

    return mapDetails;
}

map<string, CItem*> CGame::itemFactory(nlohmann::json j_room)
{
    map<string, CItem*> mapItems;
    if(j_room.count("items") == 0)
        return mapItems;

    for(auto j_item : j_room["items"])
    {
        string sName = j_item["name"];
        string sID   = j_item["id"];
        string sDescription = j_item["description"];
        string sType = j_item.value("type", "");
         
        if(sType.find("equipe") != string::npos) 
            mapItems[j_item["id"]] = new CEquippableItem(sName, sID, sDescription, sType, j_item["value"], j_item.value("hidden", false), j_item.value("function", sType));

        else
            mapItems[j_item["id"]] = new CConsumeableItem(sName, sID, sDescription, sType, j_item["effekt"], j_item["value"], j_item.value("hidden", false), j_item.value("function", sType));
        
        std::cout << "Created " << mapItems[j_item["id"]]->getName() << std::endl;
    } 
    return mapItems;
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
        map<string, CAttack*> attacks = parsePersonAttacks(j_char);

        //Create character and add to maps
        m_characters[j_char["id"]] = new CCharacter(j_char["name"], j_char["id"], j_char.value("description",""), j_char.value("hp", 30), j_char.value("strength", 7), newDialog, attacks);
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

map<string, CAttack*> CGame::parsePersonAttacks(nlohmann::json j_person)
{
    map<string, CAttack*> mapAttacks;
    if(j_person.count("attacks") == 0)
        return mapAttacks;

    objectmap person_attacks = j_person["attacks"].get<objectmap>();
    for(auto attack : person_attacks) 
        mapAttacks[attack.first] = m_attacks[attack.first];

    return mapAttacks;
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
        map<string, CAttack*> attacks = parsePersonAttacks(j_player);

        //Create player
        m_players[j_player["id"]] = new CPlayer(j_player["name"], j_player["id"], j_player.value("hp", 40), j_player.value("strength", 8), m_rooms[j_player["room"]], attacks);
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

void CGame::error(string sIdentifier) {
    m_curPlayer->appendPrint("This command is unkown.\n");
}


// *** DIALOG HANDLER *** //
void CGame::pissingman_fuckoff(string sIdentifier) {
    m_characters["pissing_man"]->setDialog(dialogFactory("defaultDialog"));
}

// *** ROOM HANDLER *** //
void CGame::firstZombieAttack(string sIdentifier)
{
    //Get selected room
    if(m_curPlayer->getRoom()->getID() != "hospital_stairs")
        return;

    m_curPlayer->appendPrint("\n$"); 
    //Create fight
    CFight* fight = new CFight("First Fight", "A zombie comes running down the stairs and attacks you!", m_curPlayer, m_characters["hospital_zombie1"]);
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
