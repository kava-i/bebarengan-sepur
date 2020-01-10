#include "CCharacter.hpp"

CCharacter::CCharacter(string sName, string sDescription, SDialog* newDialog) {
    m_sName = sName;
    m_sDescription = sDescription;
    m_dialog = newDialog;
}

// *** GETTER *** //
string CCharacter::getName() {return m_sName; }
string CCharacter::getDescription() {return m_sDescription; }
SDialog* CCharacter::getDialog() { return m_dialog; }

// *** SETTER *** //
void CCharacter::setDialog(SDialog* newDialog) { m_dialog = newDialog; };

