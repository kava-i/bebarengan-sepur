#include "CContext.hpp"
#include "CPlayer.hpp"

CContext::CContext(bool permeable, event(CContext::*parser)(string))
{
    m_permeable = permeable;
    m_parser = parser;
}

// ***** GETTER ***** // 
bool CContext::getPermeable() { return m_permeable; }

void CContext::add_listener(string sEventType, void(CContext::*handler)(string, CPlayer*))
{
    m_eventmanager[sEventType].push_back(handler);
}

void CContext::delete_listener(string sEventType, int index)
{
    m_eventmanager[sEventType].erase(m_eventmanager[sEventType].begin()+index);
}

void CContext::throw_event(std::string sInput, CPlayer* p)
{
    event newEvent = (this->*m_parser)(sInput);
    std::cout << newEvent.first << ", " << newEvent.second << "\n";

    if(m_eventmanager.count(newEvent.first) == 0) 
        return;
        
    for(auto it : m_eventmanager[newEvent.first])
        (this->*it)(newEvent.second, p);
}

void CContext::throw_event(event newEvent, CPlayer* p)
{
    if(m_eventmanager.count(newEvent.first) == 0) 
        return;
        
    for(auto it : m_eventmanager[newEvent.first])
        (this->*it)(newEvent.second, p);
}


// *** PARSER *** //
CContext::event CContext::standardParser(std::string sInput)
{
    //Create regular expressions for different command the player might have choosen
    std::regex show("((S|s)how) (.*)");
    std::regex lookIn("(L|l)(ook in )(.*)");
    std::regex pickUp("(pick up )(.*)");
    std::regex consume("(drink|eat|smoke) (.*)");
    std::regex equipe("(E|e)(quipe) (.*)");
    std::regex goTo("(G|g)(o to) (.*)");
    std::regex talkTo("(T|t)(alk to) (.*)");
    std::regex help("help");
    std::regex end("((Q|q)uit|(E|e)xit).*(game)");
    std::regex end_direct(":q");

    //Create an instans of smatch
    std::smatch m;

    //Show 
    if(std::regex_search(sInput, m, show))
        return std::make_pair("show", m[3]);
    //Look in
    else if(std::regex_search(sInput, m, lookIn))
        return std::make_pair("lookIn", m[3]); 
    //Take
    else if(std::regex_search(sInput, m, pickUp))
        return std::make_pair("take", m[2]); 
    //Consume
    else if(std::regex_search(sInput, m, consume))
        return std::make_pair("consume", m[2]); 
    //Equipe
    else if(std::regex_search(sInput, m, equipe))
        return std::make_pair("equipe", m[3]);
    //Change room
    else if(std::regex_search(sInput, m, goTo))
        return std::make_pair("goTo", m[3]);
    //Talk to 
    else if(std::regex_search(sInput, m, talkTo))
        return std::make_pair("talkTo", m[3]);
    //Help 
    else if(std::regex_match(sInput, help))
        return std::make_pair("help", "");
    else
        return std::make_pair("error", "");
}

CContext::event CContext::fightParser(string sInput)
{
    std::regex help("help");
    std::smatch m;
    if(std::regex_match(sInput, help))
        return std::make_pair("help", "fight.txt");
    else
        return std::make_pair("choose", sInput);
}

// ****************** EVENTHANDLER ********************** //

void CContext::h_show(string sIdentifier, CPlayer* p) {
    if(sIdentifier == "exits")
        p->appendPrint(p->getRoom()->showExits());
    else if(sIdentifier == "people")
        p->appendPrint(p->getRoom()->showCharacters());
    else if(sIdentifier == "room")
        p->appendPrint(p->getRoom()->showDescription(p->getWorld()->getCharacters()));
    else if(sIdentifier == "items")
        p->appendPrint(p->getRoom()->showItems());
    else if(sIdentifier == "details")
        p->appendPrint(p->getRoom()->showDetails());
    else if(sIdentifier == "inventory")
        p->printInventory();
    else if(sIdentifier == "equiped")
        p->printEquiped();
    else if(sIdentifier == "stats")
        p->appendPrint(p->showStats());
}

void CContext::h_lookIn(string sIdentifier, CPlayer* p) {
    string sOutput = p->getRoom()->look("in", sIdentifier);
    if(sOutput == "")
        p->appendPrint("Nothing found. \n");
    else
        p->appendPrint(sOutput);
}

void CContext::h_goTo(std::string sIdentifier, CPlayer* p) {

    //Get selected room
    string room = p->getObject(p->getRoom()->getExtits(), sIdentifier);

    //Check if room was found
    if(room == "") {
        p->appendPrint("Room/ exit not found");
        return;
    }

    //Print description and change players current room
    p->appendPrint(p->getWorld()->getRooms()[room]->showEntryDescription(p->getWorld()->getCharacters()));
    p->setRoom((p->getWorld()->getRooms()[room]));
}

void CContext::h_startDialog(string sIdentifier, CPlayer* p)
{
    //Get selected character
    string character = p->getObject(p->getRoom()->getCharacters(), sIdentifier);

    //Check if character was found
    if(character == "") {
        p->appendPrint("Characters not found");
        return;
    }

    //Update player status and call dialog state
    p->setDialog(p->getWorld()->getCharacters()[character]->getDialog());
    p->callDialogState("START");
}

void CContext::h_callDialog(string sIdentifier, CPlayer* p) {
    throw_event(p->callDialog(sIdentifier), p);
}

void CContext::h_choose(string sIdentifier, CPlayer* p) {
    throw_event(p->getFight()->fightRound((sIdentifier)), p); 
}

void CContext::h_take(string sIdentifier, CPlayer* p) {
    if(p->getRoom()->getItem(sIdentifier) == NULL)
        p->appendPrint("Item not found.\n");
    else
        p->addItem(p->getRoom()->getItem(sIdentifier));
}

void CContext::h_consume(string sIdentifier, CPlayer* p) {
    if(p->getItem(sIdentifier) != NULL) {
        if(p->getItem(sIdentifier)->callFunction(p) == false)
            p->appendPrint("This item is not consumeable.\n");
    }
}

void CContext::h_equipe(string sIdentifier, CPlayer* p) {
    if(p->getItem(sIdentifier) != NULL) {
        if(p->getItem(sIdentifier)->callFunction(p) == false)
            p->appendPrint("This item is not equipable.\n");
    }
}


void CContext::h_help(string sIdentifier, CPlayer* p) {
    std::ifstream read("factory/help/"+sIdentifier);

    string str((std::istreambuf_iterator<char>(read)),
                 std::istreambuf_iterator<char>());
    p->appendPrint(str);
}

void CContext::h_error(string sIdentifier, CPlayer* p) {
    p->appendPrint("This command is unkown. Type \"help\" to see possible command.\n");
}


// *** DIALOG HANDLER *** //
void CContext::h_pissingman_fuckoff(string sIdentifier, CPlayer* p) {
    p->getWorld()->getCharacters()["pissing_man"]->setDialog(p->getWorld()->dialogFactory("defaultDialog"));
}

// *** ROOM HANDLER *** //
void CContext::h_firstZombieAttack(string sIdentifier, CPlayer* p)
{
    //Get selected room
    if(p->getRoom()->getID() != "hospital_stairs")
        return;

    p->appendPrint("\n$");

    //Create fight
    CFight* fight = new CFight("First Fight", "A zombie comes running down the stairs and attacks you!", p, p->getWorld()->getCharacters()["hospital_zombie1"]);
    p->setFight(fight);
    p->setStatus("fight");
    fight->initializeFight();
    p->getContexts().push_front(new CFightContext(false, &CContext::fightParser));

    delete_listener("goTo", 1);
}

// *** FROM FIGHTS *** //
void CContext::h_deleteCharacter(string sIdentifier, CPlayer* p) {
    p->getRoom()->getCharacters().erase(sIdentifier);
    delete p->getWorld()->getCharacters()[sIdentifier];
    p->getWorld()->getCharacters().erase(sIdentifier); 
}
