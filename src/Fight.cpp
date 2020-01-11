#include "CFight.hpp"


CFight::CFight(string sName, string sDescription, CPerson* player, CPerson* opponent)
{
    m_sName = sName;
    m_sDescription = sDescription;
    m_player = player;
    m_opponent = opponent;
}

void CFight::initializeFight()
{
    m_player->appendPrint(m_sDescription + createFightingAgainst());
}

CFight::event CFight::fightRound(string sPlayerChoice)
{
    //Get selected attack
    string selectedAttack = m_player->getAttack(sPlayerChoice); 
    if(selectedAttack == "") {
        m_player->appendPrint("I can't do this!\n");
        return std::make_pair("", "");
    }
  
    string sOutput;
    //Execute players turn
    sOutput += turn(selectedAttack, m_player, m_opponent) + "$";

    //Check wether opponent is dead
    if(m_opponent->getHp() <= 0) {
        sOutput += "You defeted " + m_opponent->getName() + "!\n";
        m_player->appendPrint(sOutput);
        m_player->setStatus("standard");
        return std::make_pair("deleteCharacter", m_opponent->getID());
    }

    //Execute opponents turn
    sOutput += turn("bite", m_opponent, m_player) + "$";

    //Check wether player is dead
    if(m_player->getHp() <= 0) {
        sOutput += "You were killed! by " + m_opponent->getName() + "!\n";
        m_player->appendPrint(sOutput);
        m_player->setStatus("standard");
        return std::make_pair("gameover", "");
    }

    //Add output for next round
    sOutput += createFightingAgainst();

    //Update player print
    m_player->appendPrint(sOutput);

    //Create event
    return std::make_pair("", "");
}

string CFight::turn(string selectedAttack, CPerson* attacker, CPerson* defender)
{
    //Get selected attack 
    CAttack* attack = attacker->getAttacks()[selectedAttack];

    //Create output
    string sOutput; 
    sOutput += attacker->getName() + " uses " + attack->getName() + "\n";
    sOutput += attack->getOutput() + "\n";

    int damage = attack->getPower() + attacker->getStrength();
    sOutput += "Damage delt: " + std::to_string(damage) + "\n\n";
    defender->setHp(defender->getHp() - damage);

    return sOutput;
}


string CFight::createFightingAgainst() 
{
    std::string sOutput;
    sOutput += "\n\nFighting against eachother: \n";

    sOutput += m_player->getName() + "\n";
    sOutput += "--- HP:       " + std::to_string(m_player->getHp()) + "\n";
    sOutput += "--- Strength: " + std::to_string(m_player->getStrength()) + "\n";

    sOutput += m_opponent->getName() + "\n";
    sOutput += "--- HP:       " + std::to_string(m_opponent->getHp()) + "\n";
    sOutput += "--- Strength: " + std::to_string(m_opponent->getStrength()) + "\n\n";
    
    sOutput += "Choose an attack: \n";
    sOutput += m_player->printAttacks();

    return sOutput;
}
