#include "CCharacter.hpp"

CCharacter::CCharacter(string sName, string sDescription, SDialog* newDialog, objectmap attacks) {
    m_sName = sName;
    m_sDescription = sDescription;
    m_dialog = newDialog;
    m_attacks = attacks;

}
// *** GETTER *** //
string CCharacter::getDescription() {return m_sDescription; }


