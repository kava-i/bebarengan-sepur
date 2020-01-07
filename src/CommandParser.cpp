// *** CommandParser *** //
#include "CCommandParser.hpp"

std::pair<std::string, std::string> CCommandParser::parse(std::string sInput, std::string status)
{
    event newEvent;
    if(status=="standard")
        newEvent = parseCommand(sInput);
    else if(status.find("dialog") != std::string::npos)
        newEvent = parseDialogCommand(sInput, status);
    
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
std::pair<std::string, std::string> CCommandParser::parseCommand(std::string sInput)
{
    //Create regular expressions for different command the player might have choosen
    std::regex showExits("((S|s)how).*exits");
    std::regex goTo("(G|g)(o to) (.*)");
    std::regex showCharacters("(S|s)how.*(P|p)eople.*");
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
        newEvent = std::make_pair("showExits", "");

    //Show characters:
    else if(std::regex_match(sInput, showCharacters))
        newEvent = std::make_pair("showChars", "");

    //Change room
    else if(std::regex_search(sInput, m, goTo))
        newEvent = std::make_pair("goTo", m[3]);

    //Talk to 
    else if(std::regex_search(sInput, m, talkTo))
        newEvent = std::make_pair("talkTo", m[3]);

    return newEvent;
}

std::pair<std::string, std::string> CCommandParser::parseDialogCommand(std::string sInput, std::string status)
{
    event newEvent;
    newEvent.first = "dialog";
    newEvent.second = sInput;
    return newEvent;
}


