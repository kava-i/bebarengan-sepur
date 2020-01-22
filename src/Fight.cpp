#include "CFight.hpp"


CFight::CFight(string sName, string sDescription, CPerson* player, CPerson* opponent)
{
    m_sName = sName;
    m_sDescription = sDescription;
    m_player = player;
    m_opponent = opponent;
}

CPerson* CFight::getOpponent() { return m_opponent; }

void CFight::initializeFight()
{
    m_player->appendPrint(m_sDescription + createFightingAgainst());
}

std::string CFight::fightRound(string sPlayerChoice)
{
    string sOutput;
    //Execute players turn
    sOutput += turn(m_player->getAttack(sPlayerChoice), m_player, m_opponent) + "$";

    //Check wether opponent is dead
    if(m_opponent->getHp() <= 0) {
        sOutput += "You defeted " + m_opponent->getName() + "!\n";
        m_player->appendPrint(sOutput);
        return "endFight/deleteCharacter_" + m_opponent->getID();
    }

    //Execute opponents turn
    sOutput += turn("bite", m_opponent, m_player) + "$";

    //Check wether player is dead
    if(m_player->getHp() <= 0) {
        sOutput += "You were killed! by " + m_opponent->getName() + "!\n";
        m_player->appendPrint(sOutput);
        return "endFight/gameover";
    }

    //Add output for next round
    sOutput += "Choose an attack: \n";
    sOutput += m_player->printAttacks();

    //Update player print
    m_player->appendPrint(sOutput);

    //Create event
    return "";
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


string CFight::printStats(CPerson* person)
{
    string sOutput = person->getName() + "\n";
    sOutput += "--- HP:       " + std::to_string(person->getHp()) + "\n";
    sOutput += "--- Strength: " + std::to_string(person->getStrength()) + "\n";
    return sOutput;
}

string CFight::createFightingAgainst() 
{
    std::string sOutput;
    sOutput += "\n\nFighting against eachother: \n";

    sOutput += printStats(m_player);
    sOutput += printStats(m_opponent);
    
    sOutput += "Choose an attack: \n";
    sOutput += m_player->printAttacks();

    return sOutput;
}

