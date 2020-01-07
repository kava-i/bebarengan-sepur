#include "CCharacter.hpp"

CCharacter::CCharacter(std::string sName, dialog newDialog) {
    m_sName = sName;
    m_dialog = newDialog;
}

// *** GETTER *** //
std::string CCharacter::getName() {return m_sName; }
std::map<std::string, CDState*> CCharacter::getDialog() { return m_dialog; }

// *** SETTER *** //
void CCharacter::setDialog(dialog newDialog) { m_dialog = newDialog; };

