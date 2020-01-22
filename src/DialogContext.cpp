#include "CDialogContext.hpp"
#include "CPlayer.hpp"

void CDialogContext::h_call(string& sIdentifier, CPlayer* p)
{
    m_curState = p->getDialog()->states[m_curState]->getOptions()[stoi(sIdentifier)].sTarget;
    p->callDialogState(m_curState);
}

void CDialogContext::h_error(string&, CPlayer* p)
{
    p->appendPrint("Please choose a number, or enter \"help\".\n");
}
