#ifndef CPLAYER_H
#define CPLAYER_H

#include <iostream>
#include <map>
#include "CRoom.hpp"

class CPlayer
{
private:
    std::string m_sName;
    CRoom* m_room;

    std::string m_sPrint;

public:
    CPlayer() {};
    CPlayer(std::string sName, CRoom* room);

    // *** GETTER *** // 
    std::string getName();
    CRoom* getRoom();
    std::string getPrint();

    // *** SETTER *** //
    void setRoom(CRoom* room);
    void setPrint(std::string);
    void appendPrint(std::string);

};

#endif
    
