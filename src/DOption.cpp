#include "CDOption.hpp"

CDOption::CDOption(std::string sID, std::string sText, std::string sTarget, bool active)
{
    m_sID = sID;
    m_sText = sText;
    m_sTarget = sTarget;
    m_active = active; 
}

// *** GETTER *** //
std::string CDOption::getText() { return m_sText; }

