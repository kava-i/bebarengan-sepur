#include "CDialogContext.hpp"
#include "CPlayer.hpp"

void CDialogContext::h_call(string& sIdentifier, CPlayer* p)
{
    string nextState = p->getDialog()->states[m_curState]->getNextState(sIdentifier, p);
    if(nextState == "")
        p->appendPrint("No valid option.\n");
    else
    {
        m_curState = nextState;
        p->throw_event(p->getDialog()->states[m_curState]->callState(p));
    }
}

void CDialogContext::h_error(string&, CPlayer* p)
{
    p->appendPrint("Please choose a number, or enter \"help\".\n");
}
