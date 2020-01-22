#ifndef CCHOICECONTEXT_H
#define CCHOICECONTEXT_H

#include "CContext.hpp"

class CChoiceContext : public CContext
{
private:
    string m_sObject;
public:
    CChoiceContext(bool permeable, parser newParser, string obj) : CContext(permeable, newParser)
    {
        m_sObject=obj;
    }

    void h_choose_equipe(string&, CPlayer*);
};

#endif
