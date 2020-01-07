#include "CPlayer.hpp"

CPlayer::CPlayer(std::string sName, CRoom* room)
{
    m_sName = sName;
    m_room = room;
    m_status = "standard";
}

// *** GETTER *** // 
std::string CPlayer::getName() { return m_sName; }
CRoom* CPlayer::getRoom() { return m_room; }
std::string CPlayer::getPrint() { return m_sPrint; }
std::string CPlayer::getStatus() { return m_status; };
std::map<std::string, CDState*> CPlayer::getDialog() { return m_curDialog; }

// *** SETTER *** // 
void CPlayer::setRoom(CRoom* room) { m_room = room; }
void CPlayer::setPrint(std::string newPrint) { m_sPrint = newPrint; }
void CPlayer::appendPrint(std::string newPrint) { m_sPrint.append(newPrint); }
void CPlayer::setStatus(std::string status) { m_status = status; }
void CPlayer::setDialog(dialog newDialog) { m_curDialog = newDialog; }


