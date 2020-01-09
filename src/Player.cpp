#include "CPlayer.hpp"

CPlayer::CPlayer(std::string sName, std::string sID, CRoom* room)
{
    m_sName = sName;
    m_sID = sID;
    m_room = room;
    m_status = "standard";
}

// *** GETTER *** // 
std::string CPlayer::getName() { return m_sName; }
CRoom* CPlayer::getRoom() { return m_room; }
std::string CPlayer::getPrint() { return m_sPrint; }
std::string CPlayer::getStatus() { return m_status; };
std::map<std::string, CDState*>* CPlayer::getDialog() { return m_curDialog; }

// *** SETTER *** // 
void CPlayer::setRoom(CRoom* room) { m_room = room; }
void CPlayer::setPrint(std::string newPrint) { m_sPrint = newPrint; }
void CPlayer::appendPrint(std::string newPrint) { m_sPrint.append(newPrint); }
void CPlayer::setStatus(std::string status) { m_status = status; }
void CPlayer::setDialog(dialog* newDialog) { m_curDialog = newDialog; }

//*** FUNCTIONS *** // 

std::string CPlayer::callDialog(std::string sPlayerChoice)
{
    //Parse input
    size_t pos = m_status.find("/");
    std::string cur_id = m_status.substr(pos+1, m_status.length()-pos);
    std::string next_id = (*m_curDialog)[cur_id]->getOptions()[stoi(sPlayerChoice)]->getTargetState();

    //Call state
    callDialogState(next_id);
    return next_id;
}

void CPlayer::callDialogState(std::string sDialogStateID)
{
    //Call state
    appendPrint((*m_curDialog)[sDialogStateID]->callState());

    //Update status
    if(m_sPrint.find("Dialog ended") != std::string::npos)
        m_status = "standard";
    else
        m_status = "dialog/" + sDialogStateID;
}

std::string CPlayer::showStats() {
    std::string stats = "Name: " + m_sName + "\nID: " + m_sID + "\nStatus: " + m_status + "\n";
    return stats;
}



