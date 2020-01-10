#ifndef CPLAYER_H
#define CPLAYER_H

#include <iostream>
#include <map>
#include "CRoom.hpp"
#include "CDialog.hpp"

using std::string;

class CPlayer
{
private:
    string m_sName;
    string m_sID;
    CRoom* m_room;

    //Stats
    size_t hp;
    size_t strength;

    std::map<string, CAttack*> attacks;

    string m_sPrint;
    string m_status;

    SDialog* m_curDialog;

public:
    CPlayer() {};
    CPlayer(string sName, string sID, CRoom* room);

    // *** GETTER *** // 
    string getName();
    CRoom* getRoom();
    string getPrint();
    string getStatus();
    SDialog* getDialog();

    // *** SETTER *** //
    void setRoom(CRoom* room);
    void setPrint(string);
    void appendPrint(string);
    void setStatus(string);
    void setDialog(SDialog* newDialog);

    //*** FUNCTIONS *** // 
    string callDialog(string sPlayerChoice);
    void callDialogState(string sDialogStateID); 
    string showStats();

};

#endif
    
