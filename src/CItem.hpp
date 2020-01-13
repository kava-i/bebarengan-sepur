#ifndef CITEM_H
#define CITEM_H

#include <iostream>
#include <map>

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
    static std::map<string, string (CItem::*)(size_t& )> m_functions;

    virtual string equipeWeapon(size_t&) { return ""; }
    virtual string consumeDrug(size_t&) { return ""; }


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
    string callFunction(size_t& state);
};


class CEquippableItem : public CItem
{
private:
    string equipeWeapon(size_t& state);
public:
    CEquippableItem(string sName, string sID, string sDescription, string sType, size_t value, bool hidden, string sFunction);
};

class CConsumeableItem : public CItem
{
private:
    size_t m_effekt;
    string consumeDrug(size_t& state);
public: 
    CConsumeableItem(string sName, string sID, string sDescription, string sType, size_t effekt, size_t value, bool hidden, string sFunction);
};
#endif

 
