#include "CWorldContext.hpp"
#include "CPlayer.hpp"


void CWorldContext::h_deleteCharacter(string& sIdentifier, CPlayer* p) {
    p->getRoom()->getCharacters().erase(sIdentifier);
    delete p->getWorld()->getCharacters()[sIdentifier];
    p->getWorld()->getCharacters().erase(sIdentifier); 

    m_permeable=false;
}

void CWorldContext::h_endFight(string& sIdentifier, CPlayer* p) {
    p->endFight();
    m_permeable=false;
}

void CWorldContext::h_empty(string&, CPlayer*) {
    m_permeable=true;
}
