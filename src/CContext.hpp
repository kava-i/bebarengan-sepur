#ifndef CCONTEXT_H
#define CCONTEXT_H

#include <iostream>
#include <map>
#include <vector>
#include "func.hpp"

using std::string;
using std::map;
using std::vector;
class CPlayer; 
class CContext
{
protected:

    typedef map<string, vector<void(CContext::*)(string&, CPlayer*)>>eventmanager; 
    eventmanager m_eventmanager;

    typedef std::pair<string, string> event;

    typedef vector<event>(CContext::*parser)(std::string, CPlayer*);
    parser m_parser;
    

    bool m_permeable;

public: 
    
    CContext(bool permeable, parser newParser);
    virtual ~CContext() {}

    // *** GETTER *** //
    bool getPermeable();

    void add_listener(string sEventType, void(CContext::*)(string&, CPlayer*));
    void add_listener(string sEventType, void(CContext::*)(string&, CPlayer*), size_t pos);
    void delete_listener(string sEventType, int num);

    void throw_event(string, CPlayer* p);

    // *** PARSER *** //
    vector<event> standardParser(std::string sInput, CPlayer* p);
    vector<event> dialogParser(std::string sInput, CPlayer* p);
    vector<event> fightParser(std::string sInput, CPlayer* p);
    vector<event> worldParser(std::string sInput, CPlayer* p);
    vector<event> choiceParser(std::string sInput, CPlayer* p);

    // *** EVENTHANDLERS *** // 
    void h_help(string&, CPlayer*);

    // *** STANDARD CONTEXT *** //
    virtual void h_show             (string&, CPlayer*) {} 
    virtual void h_examine          (string&, CPlayer*) {} 
    virtual void h_lookIn           (string&, CPlayer*) {}
    virtual void h_take             (string&, CPlayer*) {}
    virtual void h_consume          (string&, CPlayer*) {}
    virtual void h_equipe           (string&, CPlayer*) {}
    virtual void h_dequipe          (string&, CPlayer*) {}
    virtual void h_goTo             (string&, CPlayer*) {}
    virtual void h_startDialog      (string&, CPlayer*) {}
    virtual void h_error            (string&, CPlayer*) {}

    //Rooms
    virtual void h_firstZombieAttack (string&, CPlayer*) {}
    virtual void h_moveToHospital    (string&, CPlayer*) {}
    virtual void h_endTutorial       (string&, CPlayer*) {}

    // *** WORLD CONTEXT *** //
    virtual void h_deleteCharacter(string&, CPlayer*) {}
    virtual void h_addItem(string&, CPlayer*) {}
    virtual void h_newFight(string&, CPlayer*) {}
    virtual void h_endFight(string&, CPlayer*) {}
    virtual void h_endDialog(string&, CPlayer*) {}
    virtual void h_empty(string&, CPlayer*) {}

    // *** FIGHT CONTEXT *** //
    virtual void h_choose(string&, CPlayer*) {}

    // *** DIALOG CONTEXT *** //
    virtual void h_call(string&, CPlayer*) {}

    // *** CHOICE CONTEXT *** //
    virtual void h_choose_equipe(string&, CPlayer*) {}

    // *** PROGRAMMER *** //
    virtual void h_try(string&, CPlayer*) {}

};



#endif


