#ifndef CITEM_H
#define CITEM_H

#include <iostream>
#include <map>

class CPlayer;

using std::string;

class CItem
{
protected:
    string m_sName;
    string m_sID;
    string m_sDescription;
    string m_sType;
    size_t m_value;
    bool m_hidden;
    string m_sFunction;

    //Static map f all state-functions
    static std::map<string, string (CItem::*)(CPlayer*)> m_functions;

    virtual string equipeWeapon(CPlayer* p) { return ""; }
    virtual string consumeDrug(CPlayer* p) { return ""; }

public:

    // *** GETTER *** // 
    string getName();
    string getID();
    string getDescription();
    string getType();
    size_t getValue();
    bool getHidden();


    // *** SETTER *** //
    void setHidden(bool hidden);

    static void initializeFunctions();
    string callFunction(CPlayer* p);
};


class CEquippableItem : public CItem
{
private:
    string equipeWeapon(CPlayer* p);
public:
    CEquippableItem(string sName, string sID, string sDescription, string sType, size_t value, bool hidden, string sFunction);
};

class CConsumeableItem : public CItem
{
private:
    size_t m_effekt;
    string consumeDrug(CPlayer* p);
public: 
    CConsumeableItem(string sName, string sID, string sDescription, string sType, size_t effekt, size_t value, bool hidden, string sFunction);
};
#endif

 
