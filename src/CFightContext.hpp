#ifndef CFIGHTCONTEXT_H
#define CFIGHTCONTEXT_H

#include "CContext.hpp"

class CFightContext : public CContext
{
public: 
    CFightContext(bool permeable, parser newParser) : CContext(permeable, newParser)
    {
        add_listener("choose", &CContext::h_choose);
        add_listener("show", &CContext::h_show);
        add_listener("attackNotFound", &CContext::h_error);
        add_listener("help", &CContext::h_help);
    }

    void h_choose(string&, CPlayer*);
    void h_show(string&, CPlayer*);
    void h_error(string&, CPlayer*);

};

#endif
