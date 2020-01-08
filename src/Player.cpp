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

//*** FUNCTIONS *** // 

void CPlayer::callDialog(std::string sPlayerChoice)
{
    size_t pos = m_status.find("/");
    std::string cur_id = m_status.substr(pos+1, m_status.length()-pos);
    std::string next_id = m_curDialog[cur_id]->getOptions()[stoi(sPlayerChoice)]->getTargetState();
    callDialogState(next_id);
}

void CPlayer::callDialogState(std::string sDialogStateID)
{
    appendPrint(m_curDialog[sDialogStateID]->getText()+"\n");

    if(m_curDialog[sDialogStateID]->getOptions().size() == 0) {
        dialogEnd(sDialogStateID);
        return;
    }

    size_t counter = 1;
    for(auto it : m_curDialog[sDialogStateID]->getOptions()) {
        appendPrint(std::to_string(counter) + ": " + it.second->getText() + "\n");
        counter++;
    }
    m_status = "dialog/" + sDialogStateID;
}

void CPlayer::dialogEnd(std::string sDialogStateID)
{
    appendPrint("Dialog ended.\n");
    m_status = "standard";
    return;
}






