#ifndef CPLAYER_H
#define CPLAYER_H

#include <iostream>
#include <map>
#include <queue>
#include <stdlib.h>
#include <chrono> 
#include <time.h>
#include <ctime>
#include "CContext.hpp"
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
using std::vector;

class CPlayer : public CPerson
{
private:
    CRoom* m_room;
    CWorld* m_world;

    size_t m_highness;

    string m_sPrint;
    string m_status;
    string m_sPassword;


    CFight* m_curFight;

    typedef map<string, vector<CItem*>> inventory;
    inventory m_inventory;
    typedef map<string, CItem*> equipment;
    equipment m_equipment;


    std::deque<CContext*> m_contextStack;

    typedef map<string, vector<std::tuple<std::chrono::system_clock::time_point, double, void(CPlayer::*)()>> > timeEvents;
    timeEvents m_timeEventes;

public:
    CPlayer() {};
    CPlayer(string sName,string password, string sID, int hp, size_t strength, CRoom* room, attacks newAttacks);


    // *** GETTER *** // 
    CRoom* getRoom();
    string getPrint();
    string getStatus();
    CFight* getFight();
    size_t getHighness();
    equipment& getEquipment();
    CWorld* getWorld();
    std::deque<CContext*>& getContexts();

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

    string doLogin(string sName, string sPassword);

    //Item and inventory
    void printInventory();
    void printEquiped();
    void addItem(CItem* item);
    void removeItem(string sItemName);
    CItem* getItem(string sName); 

    //Stats
    string showStats();

    //Others
    void checkHighness();
    typedef std::map<string, string> objectmap;
    string getObject(objectmap& mapObjects, string sIdentifier);


    void throw_event(string sInput);
    
    // *** Time events *** //

    void addTimeEvent(string sType, double duration, void(CPlayer::*func)());
    void checkTimeEvents();

    // Time handler
    void t_highness();
};

#endif
    
