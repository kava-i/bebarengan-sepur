#ifndef CPLAYER_H
#define CPLAYER_H

#include <iostream>
#include <map>
#include "CPerson.hpp"
#include "CRoom.hpp"
#include "CDialog.hpp"
#include "CAttack.hpp"

using std::string;
using std::map;

class CPlayer : public CPerson
{
private:
    CRoom* m_room;

    string m_sPrint;
    string m_status;

public:
    CPlayer() {};
    CPlayer(string sName, string sID, CRoom* room, objectmap attacks);

    // *** GETTER *** // 
    CRoom* getRoom();
    string getPrint();
    string getStatus();

    // *** SETTER *** //
    void setRoom(CRoom* room);
    void setPrint(string);
    void appendPrint(string);
    void setStatus(string);

    //*** FUNCTIONS *** // 
    string callDialog(string sPlayerChoice);
    void callDialogState(string sDialogStateID); 
    string showStats(map<string, CAttack*> attacks);

};

#endif
    
