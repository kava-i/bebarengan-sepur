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
        m_players[j_player["id"]] = new CPlayer(j_player["name"], j_player["id"], j_player.value("hp", 40), j_player.value("strength", 8), m_world->getRooms()[j_player["room"]], attacks);
    }
}



// ****************** FUNCTIONS CALLER ********************** //

string CGame::play(string sInput, string sPlayerID)
{
    //Create parser
    CCommandParser parser;

    //Create player
    m_curPlayer = m_players[sPlayerID];
    m_curPlayer->setPrint("");

    //Parse command and create event
    event newEvent = parser.parse(sInput, m_curPlayer->getStatus());

    //Throw event and delete afterwards
    m_curPlayer->throw_event(newEvent);

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


