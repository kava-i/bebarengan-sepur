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
    bool m_moveable;
    string m_sFunction;

    //Static map f all state-functions
    static std::map<string, string (CItem::*)()> m_functions;

    typedef std::map<string, string> objectmap;
    objectmap m_characters;
    objectmap m_items;

    virtual string fixxed() { return ""; }
    virtual string equipe() { return ""; }
    virtual string consume() { return ""; }


public:

    // *** GETTER *** // 
    string getName();
    string getID();
    string getDescription();
    string getType();
    virtual string getLook() { return ""; }
    size_t getValue();
    bool getHidden();
    bool getMoveable();

    virtual objectmap& getCharacters() { return m_characters; }
    virtual objectmap& getItems()      { return m_items; }

    // *** SETTER *** //
    void setHidden(bool hidden);

    static void initializeFunctions();
    string callFunction();
};


class CFixxedItem : public CItem
{
private: 
    string m_sLook;

public:
    CFixxedItem(string sName, string sID, string sDescription, string look, objectmap characters, objectmap items);

    // *** GETTER *** //
    string getLook();
    objectmap& getCharacters();
    objectmap& getItems();

    string fixxed() { std::cout << "FIXXED \n"; return ""; }
};

class CEquippableItem : public CItem
{
public:
    CEquippableItem(string sName, string sID, string sDescription, string sType, size_t value, bool hidden);
    string equipe() { std::cout << "EQUIPPED\n"; return ""; }
};

class CConsumeableItem : public CItem
{
public: 
    CConsumeableItem(string sName, string sID, string sDescription, string sType, size_t value, bool hidden);
    string consume() { std::cout << "CONSUME\n"; return ""; }
};
#endif

 
