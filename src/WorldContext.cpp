#include "CWorldContext.hpp"
#include "CPlayer.hpp"


void CWorldContext::h_deleteCharacter(string& sIdentifier, CPlayer* p) {
    p->getRoom()->getCharacters().erase(sIdentifier);
    delete p->getWorld()->getCharacters()[sIdentifier];
    p->getWorld()->getCharacters().erase(sIdentifier); 

    m_permeable=false;
}

void CWorldContext::h_addItem(string& sIdentifier, CPlayer* p) {
    p->addItem(p->getWorld()->getItem(sIdentifier));
    m_permeable=false;
}

void CWorldContext::h_endFight(string& sIdentifier, CPlayer* p) {
    p->endFight();
    m_permeable=false;
}

void CWorldContext::h_endDialog(string& sIdentifier, CPlayer* p) {
    p->deleteContext(1);
    m_permeable=false;
}

void CWorldContext::h_newFight(string& sIdentifier, CPlayer* p) {
    CFight* fight = new CFight(p, p->getWorld()->getCharacters()[sIdentifier]);
    p->setFight(fight);
}


void CWorldContext::h_empty(string&, CPlayer*) {
    m_permeable=true;
}
