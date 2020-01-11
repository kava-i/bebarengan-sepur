#ifndef CPLAYER_H
#define CPLAYER_H

#include <iostream>
#include <map>
#include "CPerson.hpp"
#include "CRoom.hpp"
#include "CDialog.hpp"
#include "CAttack.hpp"
#include "CFight.hpp"

using std::string;
using std::map;

class CPlayer : public CPerson
{
private:
    CRoom* m_room;

    string m_sPrint;
    string m_status;

    CFight* m_curFight;

public:
    CPlayer() {};
    CPlayer(string sName, string sID, int hp, size_t strength,  CRoom* room, attacks newAttacks);

    // *** GETTER *** // 
    CRoom* getRoom();
    string getPrint();
    string getStatus();
    CFight* getFight();

    // *** SETTER *** //
    void setRoom(CRoom* room);
    void setPrint(string);
    void appendPrint(string);
    void setStatus(string);
    void setFight(CFight* fight);

    //*** FUNCTIONS *** // 
    typedef std::pair<string, string> event;
    event callDialog(string sPlayerChoice);
    void callDialogState(string sDialogStateID); 
    event callFight(string sPlayerChoice);

    string showStats();
};

#endif
    
