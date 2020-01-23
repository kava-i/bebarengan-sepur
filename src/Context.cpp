#include "CContext.hpp"
#include "CPlayer.hpp"

CContext::CContext(bool permeable, parser newParser) 
{
    m_permeable = permeable;
    m_parser = newParser;
}

// ***** GETTER ***** // 
bool CContext::getPermeable() { return m_permeable; }


// **** FUNCTIONS ***** //
void CContext::add_listener(string sEventType, void(CContext::*handler)(string&, CPlayer*))
{
    m_eventmanager[sEventType].push_back(handler);
}

void CContext::add_listener(string sEventType, void(CContext::*handler)(string&, CPlayer*), size_t pos)
{
    m_eventmanager[sEventType].insert(m_eventmanager[sEventType].begin()+pos, handler);
}

void CContext::delete_listener(string sEventType, int index)
{
    m_eventmanager[sEventType].erase(m_eventmanager[sEventType].begin()+index);
}

void CContext::throw_event(std::string sInput, CPlayer* p)
{
    if(sInput == "")
        return; 
    vector<event> events = (this->*m_parser)(sInput, p);

    for(auto e : events)
    {
        std::cout << e.first << ", " << e.second << "\n";

        if(m_eventmanager.count(e.first) == 0) 
            return;
            
        for(auto it : m_eventmanager[e.first])
            (this->*it)(e.second, p);
    }
}



// *** PARSER *** //

vector<CContext::event> CContext::standardParser(std::string sInput, CPlayer* p)
{
    std::cout << "standardParser: " << sInput << std::endl;
    //Create regular expressions for different command the player might have choosen
    std::regex show("(show) (.*)");
    std::regex examine("examine");
    std::regex lookIn("(look in )(.*)");
    std::regex pickUp("(pick up )(.*)");
    std::regex consume("(drink|eat|smoke) (.*)");
    std::regex equipe("(equipe) (.*)");
    std::regex dequipe("(dequipe) (.*)");
    std::regex goTo("(go to) (.*)");
    std::regex talkTo("(talk to) (.*)");
    std::regex help("help");
    std::regex end_direct(":q");
    //Create an instans of smatch
    std::smatch m;

    //Show 
    if(std::regex_search(sInput, m, show))
        return {std::make_pair("show", m[2])};
    //Examine
    else if(std::regex_match(sInput, examine))
        return {std::make_pair("examine", "")};
    //Look in
    else if(std::regex_match(sInput, m, lookIn))
        return {std::make_pair("lookIn", m[2])};
    //Take
    else if(std::regex_match(sInput, m, pickUp))
        return {std::make_pair("take", m[2])}; 
    //Consume
    else if(std::regex_match(sInput, m, consume))
        return {std::make_pair("consume", m[2])};
    //Equipe
    else if(std::regex_match(sInput, m, equipe))
        return {std::make_pair("equipe", m[2])};
    //Dequipe
    else if(std::regex_match(sInput, m, dequipe))
        return {std::make_pair("dequipe", m[2])};
    //Change room
    else if(std::regex_match(sInput, m, goTo))
        return {std::make_pair("goTo", m[2])};
    //Talk to 
    else if(std::regex_match(sInput, m, talkTo))
        return {std::make_pair("talkTo", m[2])};
    //Help 
    else if(std::regex_match(sInput, help))
        return {std::make_pair("help", "standard.txt")};
    //Developer option
    else if(sInput == "try")
        return {std::make_pair("try", "")};
    else
        return {std::make_pair("error", "")};
}

vector<CContext::event> CContext::dialogParser(string sInput, CPlayer* p)
{
    std::cout << "dialogParser: " << sInput << std::endl;
    std::regex help("help");
    std::smatch m;
    if(std::regex_match(sInput, help))
        return {std::make_pair("help", "dialog.txt")};

    if(std::isdigit(sInput[0]) == false) 
        return {std::make_pair("error", "")};
    else
        return {std::make_pair("choose", sInput)};
}

vector<CContext::event> CContext::fightParser(string sInput, CPlayer* p)
{
    std::cout << "fightParser: " << sInput << std::endl;

    std::regex help("help");
    std::regex show("(show) (.*)");
    std::smatch m;
    if(std::regex_match(sInput, help))
        return {std::make_pair("help", "fight.txt")};
    else if(std::regex_search(sInput, m, show))
        return {std::make_pair("show", m[2])};
    
    string selectedAttack = p->getAttack(sInput);
    if(selectedAttack == "")
        return {std::make_pair("attackNotFound", "")};
    else
        return {std::make_pair("choose", sInput)};
}

vector<CContext::event> CContext::worldParser(string sInput, CPlayer* p)
{
    std::cout << "worldParser: " << sInput << std::endl;
    std::regex deleteChar("(deleteCharacter)_(.*)");
    std::regex endFight("endFight");
    std::regex endDialog("endDialog");
    std::regex fightParsen("fightParsen");
    std::smatch m;

    vector<string> commands = func::split(sInput, "/");
    vector<event> events;

    for(size_t i=0; i<commands.size(); i++)
    { 
        if(std::regex_search(commands[i], m, deleteChar))
            events.push_back(std::make_pair("deleteCharacter", m[2]));
        else if(std::regex_match(commands[i], endFight))
            events.push_back(std::make_pair("endFight", ""));
        else if(std::regex_match(commands[i], endDialog))
            events.push_back(std::make_pair("endDialog", ""));
        else if(std::regex_match(commands[i], fightParsen))
            events.push_back(std::make_pair("fightParsen", ""));
    }

    if(events.size()==0)
        return {std::make_pair("empty", "")};

    return events;
}

vector<CContext::event> CContext::choiceParser(string sInput, CPlayer* p)
{
    return {std::make_pair("choose", sInput)};
}


// ***** EVENTHANDLER ***** //
void CContext::h_help(string& sIdentifier, CPlayer* p) {
    std::ifstream read("factory/help/"+sIdentifier);

    string str((std::istreambuf_iterator<char>(read)),
                 std::istreambuf_iterator<char>());
    p->appendPrint(str);
}

