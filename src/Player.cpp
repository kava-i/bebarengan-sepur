#include "CPlayer.hpp"

CPlayer::CPlayer(string sName, string sID, CRoom* room)
{
    m_sName = sName;
    m_sID = sID;
    m_room = room;
    m_status = "standard";
}

// *** GETTER *** // 
string CPlayer::getName() { return m_sName; }
CRoom* CPlayer::getRoom() { return m_room; }
string CPlayer::getPrint() { return m_sPrint; }
string CPlayer::getStatus() { return m_status; };
SDialog* CPlayer::getDialog() { return m_curDialog; }

// *** SETTER *** // 
void CPlayer::setRoom(CRoom* room)          { m_room = room; }
void CPlayer::setPrint(string newPrint)     { m_sPrint = newPrint; }
void CPlayer::appendPrint(string newPrint)  { m_sPrint.append(newPrint); }
void CPlayer::setStatus(string status)      { m_status = status; }
void CPlayer::setDialog(SDialog* newDialog) { m_curDialog = newDialog; }

//*** FUNCTIONS *** // 

string CPlayer::callDialog(string sPlayerChoice)
{
    if(isdigit(sPlayerChoice[0]) == false) {
        appendPrint("Please choose an number\n");
        return "";
    }

    //Parse input
    size_t pos = m_status.find("/");
    string cur_id = m_status.substr(pos+1, m_status.length()-pos);
    string next_id = m_curDialog->states[cur_id]->getOptions()[stoi(sPlayerChoice)].sTarget;

    //Call state
    callDialogState(next_id);
    return m_curDialog->sName + "/" + next_id;
}

void CPlayer::callDialogState(string sDialogStateID)
{
    //Call state
    appendPrint(m_curDialog->states[sDialogStateID]->callState());

    //Update status
    if(m_sPrint.find("Dialog ended") != string::npos)
        m_status = "standard";
    else
        m_status = "dialog/" + sDialogStateID;
}

string CPlayer::showStats() {
    string stats = "Name: " + m_sName + "\nID: " + m_sID + "\nStatus: " + m_status + "\n";
    return stats;
}



