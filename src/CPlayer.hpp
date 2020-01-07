#ifndef CPLAYER_H
#define CPLAYER_H

#include <iostream>
#include <map>
#include "CRoom.hpp"
#include "CDState.hpp"

class CPlayer
{
private:
    std::string m_sName;
    CRoom* m_room;

    std::string m_sPrint;
    std::string m_status;

    typedef std::map<std::string, CDState*> dialog;
    dialog m_curDialog;

public:
    CPlayer() {};
    CPlayer(std::string sName, CRoom* room);

    // *** GETTER *** // 
    std::string getName();
    CRoom* getRoom();
    std::string getPrint();
    std::string getStatus();
    dialog getDialog();

    // *** SETTER *** //
    void setRoom(CRoom* room);
    void setPrint(std::string);
    void appendPrint(std::string);
    void setStatus(std::string);
    void setDialog(dialog newDialog);

};

#endif
    
