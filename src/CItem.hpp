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

public:

    // *** GETTER *** // 
    string getName();
    string getID();
    string getDescription();
    size_t getValue();
    bool getHidden();
};


class CFixxedItem : public CItem
{
private: 
    typedef std::map<string, string> objectmap;
    objectmap m_characters;
    objectmap m_items;

public:
    CFixxedItem(string sName, string sID, string sDescription, objectmap characters, objectmap items);

    // *** GETTER *** //
    objectmap& getCharacters();
    objectmap& getItems();
};

#endif

 
