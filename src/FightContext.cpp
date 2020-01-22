#include "CFightContext.hpp"
#include "CPlayer.hpp"

void CFightContext::h_choose(string& sIdentifier, CPlayer* p) {
    p->throw_event(p->getFight()->fightRound((sIdentifier))); 
}

void CFightContext::h_show(string& sIdentifier, CPlayer* p) {
    if(sIdentifier == "stats")
        p->appendPrint(p->getFight()->printStats(p));
    else if(sIdentifier == "opponent stats")
        p->appendPrint(p->getFight()->printStats(p->getFight()->getOpponent()));
}

void CFightContext::h_error(string&, CPlayer* p) {
    p->appendPrint("I can't do this. Please choose an attack, or use help.\n");
}
