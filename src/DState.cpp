#include "CDState.hpp"

CDState::CDState(std::string sID, std::string sText, std::string func, dialogoptions opts, dialog* dia)
{
    m_sID = sID;
    m_sText = sText;
    m_sFunction = func;
    m_options = opts;
    m_dialog = dia;
}

// *** GETTER *** //
std::string CDState::getText() { return m_sText; }
std::map<int, CDOption*>& CDState::getOptions() { return m_options; }

// *** FUNCTIONS *** // 

std::map<std::string, std::string (CDState::*)()> CDState::m_functions = {};
void CDState::initializeFunctions()
{
    m_functions["standard"] = &CDState::standard;
    m_functions["parsen1"]  = &CDState::parsen1;
}

std::string CDState::callState() {
    return (this->*m_functions[m_sFunction])();
}

std::string CDState::standard()
{
    std::string sOutput = m_sText + "\n";

    if(numOptions() == 0)
        return sOutput + "Dialog ended. \n";

    size_t numOpts = numOptions();
    for(size_t i=1; i<numOpts+1; i++)
        sOutput += std::to_string(i) + ": " + m_options[i]->getText() + "\n";

    return sOutput;
}

std::string CDState::parsen1()
{
    std::cout << "called parsen1() \n";
    std::string sOutput = standard();
    addDialogOption("START", -1);
    deleteDialogOption("START", 1);
    m_sFunction = "standard";
    return sOutput;
}

void CDState::addDialogOption(std::string sStateID, size_t optID) {
    (*m_dialog)["START"]->getOptions()[(*m_dialog)["START"]->numOptions()+1] = (*m_dialog)["START"]->getOptions()[-1];
}

void CDState::deleteDialogOption(std::string sStateID, size_t optID) {
    (*m_dialog)["START"]->getOptions().erase(optID);
} 
     

size_t CDState::numOptions()
{
    size_t counter = 0;
    for(auto it : m_options) {
        if(it.first > 0)
            counter++;
    }
    return counter;
}
        




