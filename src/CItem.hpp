#ifndef CITEM_H
#define CITEM_H

#include <iostream>
#include <map>
#include "json.hpp"

class CPlayer;

using std::string;

class CItem
{
protected:

    nlohmann::json m_jAtts;

    //Static map f all state-functions
    static std::map<string, string (CItem::*)(CPlayer*)> m_functions;

public:

    CItem(nlohmann::json jAtts);

    // *** GETTER *** // 
    template <typename T> T getAttribute(std::string sName)
    {
        if(m_jAtts.count(sName) == 0)
            return T();
        return m_jAtts[sName].get<T>();
    }
    
    // *** SETTER *** //
    template <typename T> void setAttribute(std::string sName, T t1)
    {
        m_jAtts[sName] = t1;
    }

    static void initializeFunctions();
    string callFunction(CPlayer* p);

    // *** FUNCTIONS *** //
    string equipeWeapon(CPlayer*);
    string consumeDrug(CPlayer*);
};

#endif

 
