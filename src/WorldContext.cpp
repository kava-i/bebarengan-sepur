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

void CWorldContext::h_endDialog(string& sIdentifier, CPlayer* p) {
    p->deleteContext(1);
    m_permeable=false;
}

void CWorldContext::h_fightParsen(string&, CPlayer* p) {
    //Create fight
    CFight* fight = new CFight("Fight Parsen", "Parsen krempelt seine Arme hoch und macht sicht bereit. Er sieht ein klein wneig lächerlich aus. Gewalt scheint ihm nicht sonderlich zu stehen.", p, p->getWorld()->getCharacters()["parsen"]);
    p->setFight(fight);
}


void CWorldContext::h_empty(string&, CPlayer*) {
    m_permeable=true;
}
