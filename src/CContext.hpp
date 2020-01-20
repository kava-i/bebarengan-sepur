#ifndef CCONTEXT_H
#define CCONTEXT_H

#include <iostream>
#include <map>
#include <vector>

using std::string;
using std::map;
using std::vector;

class CPlayer;

class CContext
{
protected:

    typedef map<string, vector<void(CContext::*)(string, CPlayer*)>>eventmanager; 
    eventmanager m_eventmanager;

    typedef std::pair<string, string> event;
    event(CContext::*m_parser)(std::string);

    bool m_permeable;

public: 
    
    CContext(bool permeable, event(CContext::*parser)(string));

    // *** GETTER *** //
    bool getPermeable();

    void add_listener(string sEventType, void(CContext::*)(string, CPlayer*));
    void delete_listener(string sEventType, int num);

    void throw_event(string, CPlayer* p);
    void throw_event(event newEvent, CPlayer* p);

    // *** PARSER *** //
    event standardParser(std::string sInput);
    event dialogParser(std::string sInput);
    event fightParser(std::string sInput);

    // *** EVENTHANDLERS *** // 
    void h_show             (string sIdentiier, CPlayer* p);
    void h_lookIn           (string sIdentiier, CPlayer* p);
    void h_take             (string sIdentiier, CPlayer* p);
    void h_consume          (string sIdentiier, CPlayer* p);
    void h_equipe           (string sIdentiier, CPlayer* p);
    void h_goTo             (string sIdentiier, CPlayer* p);
    void h_startDialog      (string sIdentiier, CPlayer* p);
    void h_callDialog       (string sIdentiier, CPlayer* p);
    void h_callFight        (string sIdentiier, CPlayer* p);
    void h_help             (string sIdentiier, CPlayer* p);
    void h_error            (string sIdentiier, CPlayer* p);
    void h_deleteCharacter  (string sIdentiier, CPlayer* p);
    
    //Dialogs
    void h_pissingman_fuckoff (string sIdentiier, CPlayer* p);

    //Rooms
    void h_firstZombieAttack (string sIdentiier, CPlayer* p);


    //FIGHTCONTEXT
    void h_choose(string, CPlayer* p);

};

class CStandardContext : public CContext
{
public:
    CStandardContext(bool permeable, event(CContext::*parser)(string)) : CContext(permeable, parser)
    {
        add_listener("show", &CContext::h_show);
        add_listener("lookIn", &CContext::h_lookIn);
        add_listener("goTo", &CContext::h_goTo);
        add_listener("talkTo", &CContext::h_startDialog);
        add_listener("dialog", &CContext::h_callDialog);
        add_listener("fight", &CContext::h_callFight);
        add_listener("take", &CContext::h_take);
        add_listener("consume", &CContext::h_consume);
        add_listener("equipe", &CContext::h_equipe);
        add_listener("help", &CContext::h_help);
        add_listener("error", &CContext::h_error);
        add_listener("deleteCharacter", &CContext::h_deleteCharacter);

        //Dialogs
        add_listener("pissingManDialog/fuckoff", &CContext::h_pissingman_fuckoff);

        //Rooms
        add_listener("goTo", &CContext::h_firstZombieAttack);
    }
};

class CFightContext : public CContext
{
public: 
    CFightContext(bool permeable, event(CContext::*parser)(string)) : CContext(permeable, parser)
    {
        add_listener("choose", &CContext::h_choose);
        add_listener("help", &CContext::h_help);
        add_listener("error", &CContext::h_error);
    }
};

#endif


