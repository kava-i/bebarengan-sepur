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
    size_t m_value;
    bool m_hidden;
    bool m_moveable;

    typedef std::map<string, string> objectmap;

public:

    // *** GETTER *** // 
    string getName();
    string getID();
    string getDescription();
    virtual string getLook() { return ""; }
    size_t getValue();
    bool getHidden();

    virtual objectmap& getCharacters() { objectmap x; return x; }
    virtual objectmap& getItems()      { objectmap x; return x; }

    // *** SETTER *** //
    void setHidden(bool hidden);
};


class CFixxedItem : public CItem
{
private: 
    string m_sLook;
    objectmap m_characters;
    objectmap m_items;

public:
    CFixxedItem(string sName, string sID, string sDescription, string look, objectmap characters, objectmap items);

    // *** GETTER *** //
    string getLook();
    objectmap& getCharacters();
    objectmap& getItems();
};

class CEquippableItem : public CItem
{
public:
    CEquippableItem(string sName, string sID, string sDescription, size_t value, bool hidden);
};

#endif

 
