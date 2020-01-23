#ifndef CWORLDCONTEXT_H
#define CWORLDCONTEXT_H

#include "CContext.hpp"

class CWorldContext : public CContext
{
public:
    CWorldContext(bool permeable, parser newParser) : CContext(permeable, newParser)
    {
        add_listener("deleteCharacter", &CContext::h_deleteCharacter);
        add_listener("endFight", &CContext::h_endFight);
        add_listener("endDialog", &CContext::h_endDialog);
        add_listener("fightParsen", &CContext::h_fightParsen);
        add_listener("empty", &CContext::h_empty);
    }

    void h_deleteCharacter(string&, CPlayer*);
    void h_endFight(string&, CPlayer*);
    void h_endDialog(string&, CPlayer*);
    void h_fightParsen(string&, CPlayer*);
    void h_empty(string&, CPlayer*);
};

#endif
