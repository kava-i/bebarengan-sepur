#include "CCharacter.hpp"

CCharacter::CCharacter(std::string sName, std::string sDescription, dialog* newDialog) {
    m_sName = sName;
    m_sDescription = sDescription;
    m_dialog = newDialog;
}

// *** GETTER *** //
std::string CCharacter::getName() {return m_sName; }
std::string CCharacter::getDescription() {return m_sDescription; }
std::map<std::string, CDState*>* CCharacter::getDialog() { return m_dialog; }

// *** SETTER *** //
void CCharacter::setDialog(dialog* newDialog) { m_dialog = newDialog; };

