#include "CDState.hpp"

CDState::CDState(std::string sID, std::string sText, std::map<size_t, CDOption*> optiones)
{
    m_sID = sID;
    m_sText = sText;
    m_options = optiones;
}

// *** GETTER *** //
std::string CDState::getText() { return m_sText; }
std::map<size_t, CDOption*> CDState::getOptions() { return m_options; }


