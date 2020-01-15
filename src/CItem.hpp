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
    static std::map<string, void (CItem::*)(CPlayer*)> m_consumeFunctions;
    static std::map<string, void (CItem::*)(CPlayer*)> m_equipeFunctions;

public:

    CItem(nlohmann::json jBasic, nlohmann::json jItem);

    // *** GETTER *** // 
    template <typename T> T getAttribute(std::string sName)
    {
        if(m_jAtts.count(sName) == 0)
            return T();
        return m_jAtts[sName].get<T>();
    }

    string getID();
    string getName();
    string getFunction();
    size_t getEffekt();
    
    // *** SETTER *** //
    template <typename T> void setAttribute(std::string sName, T t1)
    {
        m_jAtts[sName] = t1;
    }

    static void initializeConsumeFunctions();
    void callConsumeFunction(CPlayer* p);
    static void initializeEquipeFunctions();
    void callEquipeFunction(CPlayer* p);

    // *** FUNCTIONS *** //
    void equipeWeapon(CPlayer*);
    void consumeDrug(CPlayer*);
};

#endif

 
