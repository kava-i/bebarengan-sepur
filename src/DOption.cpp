#include "CDOption.hpp"

CDOption::CDOption(size_t ID, std::string sText, std::string sTarget, bool active)
{
    m_ID = ID;
    m_sText = sText;
    m_sTarget = sTarget;
    m_active = active; 
}

// *** GETTER *** //
std::string CDOption::getText() { return m_sText; }
std::string CDOption::getTargetState() { return m_sTarget; }

