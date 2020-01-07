/**
* CCommandparser.hpp
* The class command parser contains various functions (currently only one) to parse a command
* into an event.
*/

#ifndef CCOMMANDPARSER_H 
#define CCOMMANDPARSER_H 

#include <iostream>
#include <algorithm>
#include <string>
#include <regex>

class CCommandParser
{
public:
    typedef std::pair<std::string, std::string> event;

    event parse(std::string sInput, std::string status);

    /**
    * parseCommand: parse a command the player enter into an event. 
    * @parameter string (player input)
    * @return CEvent* (Pointer to event created)
    */
    event parseCommand(std::string sInput);
    event parseDialogCommand(std::string sInput, std::string status);
};

#endif

    
