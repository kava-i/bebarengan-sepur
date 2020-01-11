#include "CPerson.hpp"

// *** GETTER *** //

string CPerson::getName()       { return m_sName; }
int CPerson::getHp()            { return m_hp; }
size_t CPerson::getStrength()   { return m_strength; }
SDialog* CPerson::getDialog()   { return m_dialog; }
CPerson::objectmap CPerson::getAttacks() { return m_attacks; }

// *** SETTER *** //
void CPerson::setDialog(SDialog* newDialog) { m_dialog = newDialog; }
