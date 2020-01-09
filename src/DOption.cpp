#include "CDOption.hpp"

CDOption::CDOption(std::string sText, std::string sTarget)
{
    m_sText = sText;
    m_sTarget = sTarget;
}

// *** GETTER *** //
std::string CDOption::getText() { return m_sText; }
std::string CDOption::getTargetState() { return m_sTarget; }

