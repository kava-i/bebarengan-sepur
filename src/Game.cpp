#include "CGame.hpp"


CGame::CGame() {
    m_world = new CWorld();

    //Create players
    playerFactory();
    std::cout << "Finished parsing!\n";
}

void CGame::playerFactory()
{
    std::cout << "Parsing players... \n";

    //Read json creating all rooms
    std::ifstream read("factory/jsons/players/players.json");
    nlohmann::json j_players;
    read >> j_players;
    read.close();

    for(auto j_player : j_players) {

        //Create attacks
        map<string, CAttack*> attacks = m_world->parsePersonAttacks(j_player);

        //Create player
        m_players[j_player["id"]] = new CPlayer(j_player["name"], j_player["password"],j_player["id"], j_player.value("hp", 40), j_player.value("strength", 8), j_player.value("gold", 5), m_world->getRooms()[j_player["room"]], attacks);
    }
}


string CGame::checkLogin(string sName, string sPassword)
{
    for(auto &it : m_players)
    {
	string tmp = it.second->doLogin(sName,sPassword);
	if(tmp != "")
	    return tmp;
    }
    return "";
}

// ****************** FUNCTIONS CALLER ********************** //

string CGame::startGame(string sInput, string sPasswordID)
{
    if(m_players[sPasswordID]->getFirstLogin() == true) {
        m_players[sPasswordID]->throw_event("startTutorial");
        m_players[sPasswordID]->setFirstLogin(false);
    }
    else
        m_players[sPasswordID]->throw_event("show room");

    return m_players[sPasswordID]->getPrint();
}

string CGame::play(string sInput, string sPlayerID, list<string>& onlinePlayers)
{
    func::convertToLower(sInput);    

    std::map<string, string> mapOnlinePlayers;
    for(auto it : onlinePlayers)
    {
        if(it.first != m_players[sPlayerID]->getID())
            mapOnlinePlayers[m_players[(*it)]->getName()] = m_players[(*it)]->getRoom()->getID();
    }
            
    //Create player
    m_curPlayer = m_players[sPlayerID];
    m_curPlayer->setPrint("");
    m_curPlayer->getRoom()->setPlayers(mapOnlinePlayers);

    //Throw event 
    m_curPlayer->throw_event(sInput);

    return m_curPlayer->getPrint(); 
}

    


/*
void CGame::toJson(string filename)
{
    //Convert yaml to json using python
	Py_Initialize();
	FILE* fp = _Py_fopen(filename, "r");
	PyRun_SimpleFile(fp, filename);

	Py_Finalize();
}
*/ 


