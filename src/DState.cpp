#include "CDState.hpp"

CDState::CDState(std::string sID, std::string sText, std::string func, std::vector<std::string> alternativeTexts, dialogoptions opts, dialog* dia)
{
    m_sID = sID;
    m_sText = sText;
    m_sFunction = func;
    m_alternativeTexts = alternativeTexts;
    m_options = opts;
    m_dialog = dia;
}

// *** GETTER *** //
std::string CDState::getText() { return m_sText; }
CDState::dialogoptions& CDState::getOptions() { return m_options; }

// *** SETTER *** //
void CDState::setText(size_t text) { m_sText = m_alternativeTexts[text]; }

// *** FUNCTIONS *** // 

std::map<std::string, std::string (CDState::*)()> CDState::m_functions = {};
void CDState::initializeFunctions()
{
    m_functions["standard"]     = &CDState::standard;
    m_functions["parsen1"]      = &CDState::parsen1;
}

std::string CDState::callState() {
    return (this->*m_functions[m_sFunction])();
}

// *** FUNCTION POINTER *** //
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
    std::string sOutput = standard();
    addDialogOption("START", -1);       //Add new option (4)
    deleteDialogOption("START", 1);     //Delete old option (1)
    changeStateText("START", 0);        //Change text (0)
    m_sFunction = "standard";           
    return sOutput;
}

// *** VARIOUS FUNCTIONS *** // 
void CDState::changeStateText(std::string sStateID, size_t text) {
    (*m_dialog)["START"]->setText(text);
}
void CDState::addDialogOption(std::string sStateID, size_t optID) {
    (*m_dialog)["START"]->getOptions()[(*m_dialog)["START"]->numOptions()+1] = (*m_dialog)["START"]->getOptions()[-1];
}

void CDState::deleteDialogOption(std::string sStateID, size_t optID) {
    (*m_dialog)["START"]->getOptions().erase(optID);

    for(size_t i=optID+1; i<(*m_dialog)["START"]->numOptions()+2; i++)
    {
        auto nodeHandler = (*m_dialog)["START"]->getOptions().extract(i);
        nodeHandler.key() = i-1;
        (*m_dialog)["START"]->getOptions().insert(std::move(nodeHandler));
    }
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
        
