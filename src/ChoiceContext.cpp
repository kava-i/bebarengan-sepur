#include "CChoiceContext.hpp"
#include "CPlayer.hpp"



// ***** PARSER ***** //

vector<CContext::event> CChoiceContext::parser(string sInput, CPlayer* p)
{
    return {std::make_pair("choose", sInput)};
}


// ***** Handlers ***** //

void CChoiceContext::h_choose_equipe(string& sIdentifier, CPlayer* p)
{
    std::cout << "h_choose_equipe: " << sIdentifier << " " << m_sObject << std::endl;
    if(sIdentifier == "yes")
    {
        p->dequipeItem("weapon");
        p->equipeItem(p->getItem_byID(m_sObject), "weapon");
        p->deleteContext(1);
    }

    else if(sIdentifier == "no")
    {
        std::cout << "1." << std::endl;
        p->appendPrint("You chose not to equipe " + p->getItem_byID(m_sObject)->getName() + ".\n");
        std::cout << "2." << std::endl;
        p->deleteContext(1);
        std::cout << "3." << std::endl;
    }

    else
        p->appendPrint("Worng input. Use \"help\" if you're unsure what to do.\n");

}
