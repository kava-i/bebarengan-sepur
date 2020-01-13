// *** CommandParser *** //
#include "CCommandParser.hpp"

CCommandParser::event CCommandParser::parse(std::string sInput, std::string status)
{
    event newEvent;
    if(status=="standard")
        newEvent = parseCommand(sInput);
    else if(status.find("dialog") != std::string::npos)
        newEvent = parseDialogCommand(sInput, status);
    else if(status == "fight")
        newEvent = std::make_pair("fight", sInput);
    
    return newEvent;
}

/**
* parseCommand: parse a command the player enter into an event. The event contains an event type
* what does the player want to do. F.e. "changeRoom" in case the player wants to go somewhere and
* an identifier providing additional information, in our example where the player wants to go to. 
* Assuming the player entered "go to kitchen" the string will be parsed into an event with event 
* type "changeRoom" and identifier "kitchen". 
* @parameter string (player input)
* @return CEvent* (Pointer to event created)
*/
CCommandParser::event CCommandParser::parseCommand(std::string sInput)
{
    //Create regular expressions for different command the player might have choosen
    std::regex showExits("((S|s)how).*exits");
    std::regex showCharacters("(S|s)how.*(P|p)eople.*");
    std::regex showDescription("(S|s)how.*(R|r)oom.*");
    std::regex showItems("(S|s)how.*(I|i)tems.*");
    std::regex showDetails("(S|s)how.*(D|d)etails.*");
    std::regex showInventory("(S|s)how.*(I|i)nventory.*");
    std::regex showStats("(S|s)how.*(S|s)tats.*");
    std::regex lookIn("(L|l)(ook in )(.*)");
    std::regex take("(take )(.*)");
    std::regex use("(use )(.*)");
    std::regex goTo("(G|g)(o to) (.*)");
    std::regex talkTo("(T|t)(alk to) (.*)");
    //std::regex showActive("(((Z|z)eig(e?) )?.*((A|a)ktive(n?))? (Q|q)uests)");
    //std::regex showSolved("(((Z|z)eig(e?) )?.*(G|g)elöste(n?) (Q|q)uests)");
    std::regex end("((Q|q)uit|(E|e)xit).*(game)");
    std::regex end_direct(":q");

    //Create an instans of smatch
    std::smatch m;

    //Check which regular expression the players input matches. Create and return event if match
    event newEvent;

    //Show exits:
    if(std::regex_match(sInput, showExits))
        newEvent = std::make_pair("show", "exits");

    //Show characters:
    else if(std::regex_match(sInput, showCharacters))
        newEvent = std::make_pair("show", "chars");

    //Show description:
    else if(std::regex_match(sInput, showDescription))
        newEvent = std::make_pair("show", "room");
    
    //Show items
    else if(std::regex_match(sInput, showItems))
        newEvent = std::make_pair("show", "items");

    //Show details
    else if(std::regex_match(sInput, showDetails))
        newEvent = std::make_pair("show", "details");

    //Show inventory
    else if(std::regex_match(sInput, showInventory))
        newEvent = std::make_pair("show", "inventory");

    //Show stats:
    else if(std::regex_match(sInput, showStats))
        newEvent = std::make_pair("show", "stats");

    //Look in
    else if(std::regex_search(sInput, m, lookIn))
        newEvent = std::make_pair("lookIn", m[3]); 

    //Take
    else if(std::regex_search(sInput, m, take))
        newEvent = std::make_pair("take", m[2]); 

    //Use
    else if(std::regex_search(sInput, m, use))
        newEvent = std::make_pair("use", m[2]); 

    //Change room
    else if(std::regex_search(sInput, m, goTo))
        newEvent = std::make_pair("goTo", m[3]);

    //Talk to 
    else if(std::regex_search(sInput, m, talkTo))
        newEvent = std::make_pair("talkTo", m[3]);

    else
        newEvent = std::make_pair("error", "");

    return newEvent;
}

CCommandParser::event CCommandParser::parseDialogCommand(std::string sInput, std::string status)
{
    event newEvent;
    newEvent.first = "dialog";
    newEvent.second = sInput;
    return newEvent;
}


