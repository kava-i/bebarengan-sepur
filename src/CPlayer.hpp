#ifndef CPLAYER_H
#define CPLAYER_H

#include <iostream>
#include <map>
#include <stdlib.h>
#include <time.h>
#include "CWorld.hpp"
#include "CPerson.hpp"
#include "CRoom.hpp"
#include "CDialog.hpp"
#include "CAttack.hpp"
#include "CFight.hpp"
#include "func.hpp"

#include "JanGeschenk/Webconsole.hpp"
#include "JanGeschenk/Webgame.hpp"
 
using std::string;
using std::map;

class CPlayer : public CPerson
{
private:
    CRoom* m_room;
    CWorld* m_world;

    size_t m_highness;

    string m_sPrint;
    string m_status;

    CFight* m_curFight;

    typedef map<string, vector<CItem*>> inventory;
    inventory m_inventory;

    typedef map<string, vector<void(CPlayer::*)(string)>>eventmanager; 
    eventmanager m_eventmanager;

public:
    CPlayer() {};
    CPlayer(string sName, string sID, int hp, size_t strength, CRoom* room, attacks newAttacks);

    // *** GETTER *** // 
    CRoom* getRoom();
    string getPrint();
    string getStatus();
    CFight* getFight();
    size_t getHighness();

    // *** SETTER *** //
    void setRoom(CRoom* room);
    void setPrint(string);
    void appendPrint(string);
    void setStatus(string);
    void setFight(CFight* fight);
    void setHighness(size_t highness);

    //*** FUNCTIONS *** // 
    typedef std::pair<string, string> event;
    event callDialog(string sPlayerChoice);
    void callDialogState(string sDialogStateID); 
    event callFight(string sPlayerChoice);
    
    void printInventory();
    void addItem(CItem* item);
    void useItem(string sPlayerChoice);
    void removeItem(string sItemName);
    string showStats();

    void checkHighness();

    typedef std::map<string, string> objectmap;
    string getObject(objectmap& mapObjects, string sIdentifier);

    // *** Event Manager function *** // 
    void throw_event(event newEvent);

    // *** EVENTHANDLERS *** // 
    void h_show             (string sIdentifier);
    void h_lookIn           (string sIdentifier);
    void h_take             (string sIdentifier);
    void h_use              (string sIdentifier);
    void h_goTo             (string sIdentifier);
    void h_startDialog      (string sIdentifier);
    void h_callDialog       (string sIdentifier);
    void h_callFight        (string sIdentifier);
    void h_help             (string sIdentifier);
    void h_error            (string sIdentifier);
    void h_deleteCharacter  (string sIdentifier);
    
    //Dialogs
    void h_pissingman_fuckoff (string sIdentifier);

    //Rooms
    void h_firstZombieAttack (string sIdentifier);
};

#endif
    
