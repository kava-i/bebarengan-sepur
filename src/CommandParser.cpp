// *** CommandParser *** //
#include "CCommandParser.hpp"

CCommandParser::event CCommandParser::parse(std::string sInput, std::string status)
{
    event newEvent;

    //Parse status independat...
    if(sInput == "help" && status.find("dialog") != std::string::npos)
        newEvent = std::make_pair("help", "dialog.txt");
    else if(sInput == "help")
        newEvent = std::make_pair("help", status +".txt");


    else if(status=="standard")
        newEvent = parseCommand(sInput);
    else if(status.find("dialog") != std::string::npos)
        newEvent = std::make_pair("dialog", sInput);
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

    //Check which regular expression the players input matches. Create and return event if match
    event newEvent;

    //Show 
    if(std::regex_search(sInput, m, show))
        newEvent = std::make_pair("show", m[3]);
    
    //Look in
    else if(std::regex_search(sInput, m, lookIn))
        newEvent = std::make_pair("lookIn", m[3]); 

    //Take
    else if(std::regex_search(sInput, m, pickUp))
        newEvent = std::make_pair("take", m[2]); 

    //Consume
    else if(std::regex_search(sInput, m, consume))
        newEvent = std::make_pair("consume", m[2]); 

    //Equipe
    else if(std::regex_search(sInput, m, equipe))
        newEvent = std::make_pair("equipe", m[3]);

    //Change room
    else if(std::regex_search(sInput, m, goTo))
        newEvent = std::make_pair("goTo", m[3]);

    //Talk to 
    else if(std::regex_search(sInput, m, talkTo))
        newEvent = std::make_pair("talkTo", m[3]);

    //Help 
    else if(std::regex_match(sInput, help))
        newEvent = std::make_pair("help", "");

    else
        newEvent = std::make_pair("error", "");

    return newEvent;
}

