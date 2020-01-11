#include "CPlayer.hpp"

CPlayer::CPlayer(string sName, string sID, CRoom* room, objectmap attacks)
{
    m_sName = sName;
    m_sID = sID;
    m_room = room;
    m_status = "standard";
    m_attacks = attacks;
}

// *** GETTER *** // 
CRoom* CPlayer::getRoom()   { return m_room; }
string CPlayer::getPrint()  { return m_sPrint; }
string CPlayer::getStatus() { return m_status; };

// *** SETTER *** // 
void CPlayer::setRoom(CRoom* room)          { m_room = room; }
void CPlayer::setPrint(string newPrint)     { m_sPrint = newPrint; }
void CPlayer::appendPrint(string newPrint)  { m_sPrint.append(newPrint); }
void CPlayer::setStatus(string status)      { m_status = status; }

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
    string next_id = m_dialog->states[cur_id]->getOptions()[stoi(sPlayerChoice)].sTarget;

    //Call state
    callDialogState(next_id);
    return m_dialog->sName + "/" + next_id;
}

void CPlayer::callDialogState(string sDialogStateID)
{
    //Call state
    appendPrint(m_dialog->states[sDialogStateID]->callState());

    //Update status
    if(m_sPrint.find("Dialog ended") != string::npos)
        m_status = "standard";
    else
        m_status = "dialog/" + sDialogStateID;
}

string CPlayer::showStats(map<string, CAttack*> attacks) {
    string stats = "Name: " + m_sName + "\nID: " + m_sID + "\nStatus: " + m_status + "\n";
    stats += "Attacks: \n";
    for(auto attack : m_attacks)
        stats += "-> " + attack.second + ": " + attacks[attack.first]->getDescription() + "\n";

    return stats;
}



