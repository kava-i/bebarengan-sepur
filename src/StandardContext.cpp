#include "CStandardContext.hpp"
#include "CPlayer.hpp"

void CStandardContext::h_show(string& sIdentifier, CPlayer* p) {
    if(sIdentifier == "exits")
        p->appendPrint(p->getRoom()->showExits());
    else if(sIdentifier == "people")
        p->appendPrint(p->getRoom()->showCharacters());
    else if(sIdentifier == "room")
        p->appendPrint(p->getRoom()->showDescription(p->getWorld()->getCharacters()));
    else if(sIdentifier == "items")
        p->appendPrint(p->getRoom()->showItems());
    else if(sIdentifier == "details")
        p->appendPrint(p->getRoom()->showDetails());
    else if(sIdentifier == "inventory")
        p->printInventory();
    else if(sIdentifier == "equiped")
        p->printEquiped();
    else if(sIdentifier == "stats")
        p->appendPrint(p->showStats());
    else if(sIdentifier == "all")
        p->appendPrint(p->getRoom()->showAll());
}

void CStandardContext::h_examine(string& sIdentifier, CPlayer* p) {
    p->appendPrint(p->getRoom()->showAll());
}

void CStandardContext::h_lookIn(string& sIdentifier, CPlayer* p) {
    string sOutput = p->getRoom()->look("in", sIdentifier);
    if(sOutput == "")
        p->appendPrint("Nothing found. \n");
    else
        p->appendPrint(sOutput);
}

void CStandardContext::h_goTo(std::string& sIdentifier, CPlayer* p) {
    //Get selected room
    string room = p->getObject(p->getRoom()->getExtits(), sIdentifier);

    //Check if room was found
    if(room == "") {
        p->appendPrint("Room/ exit not found");
        return;
    }

    //Print description and change players current room
    p->appendPrint(p->getWorld()->getRooms()[room]->showEntryDescription(p->getWorld()->getCharacters()));
    p->setRoom((p->getWorld()->getRooms()[room]));
}

void CStandardContext::h_startDialog(string& sIdentifier, CPlayer* p)
{
    //Get selected character
    string character = p->getObject(p->getRoom()->getCharacters(), sIdentifier);

    //Check if character was found
    if(character == "") {
        p->appendPrint("Characters not found");
        return;
    }

    //Update player status and call dialog state
    p->newContext(new CDialogContext(false, &CContext::dialogParser), 1);
    p->setDialog(p->getWorld()->getCharacters()[character]->getDialog());

    p->throw_event(p->getDialog()->states["START"]->callState(p));
}

void CStandardContext::h_take(string& sIdentifier, CPlayer* p) {
    if(p->getRoom()->getItem(sIdentifier) == NULL)
        p->appendPrint("Item not found.\n");
    else
        p->addItem(p->getRoom()->getItem(sIdentifier));
}

void CStandardContext::h_consume(string& sIdentifier, CPlayer* p) {
    if(p->getItem(sIdentifier) != NULL) {
        if(p->getItem(sIdentifier)->callFunction(p) == false)
            p->appendPrint("This item is not consumeable.\n");
    }
}

void CStandardContext::h_equipe(string& sIdentifier, CPlayer* p) {
    if(p->getItem(sIdentifier) != NULL) {
        if(p->getItem(sIdentifier)->callFunction(p) == false)
            p->appendPrint("This item is not equipable.\n");
    }
}

void CStandardContext::h_dequipe(string& sIdentifier, CPlayer* p) {
    p->dequipeItem(sIdentifier);
}

void CStandardContext::h_error(string& sIdentifier, CPlayer* p) {
    p->appendPrint("This command is unkown. Type \"help\" to see possible command.\n");
}


void CStandardContext::h_firstZombieAttack(string& sIdentifier, CPlayer* p)
{
    //Get selected room
    if(p->getRoom()->getID() != "hospital_stairs")
        return;

    p->appendPrint("\n$");

    //Create fight
    CFight* fight = new CFight("First Fight", "A zombie comes running down the stairs and attacks you!", p, p->getWorld()->getCharacters()["hospital_zombie1"]);
    p->setFight(fight);

    delete_listener("goTo", 2);
}

void CStandardContext::h_moveToHospital(string& sIdentifier, CPlayer* p)
{
    std::cout << "h_moveToHospital: " << sIdentifier << std::endl;
    //Get selected room
    if(p->getRoom()->getID().find("compartment") == std::string::npos)
        return;

    sIdentifier = "Foyer";
    p->setRoom(p->getWorld()->getRooms()["hospital_stairs"]);
}

void CStandardContext::h_endTutorial(string& sIdentifier, CPlayer* p)
{
    std::cout << "h_endTutorial: " << sIdentifier << std::endl;
    if(p->getRoom()->getID().find("gleis3") == std::string::npos)
        return;
    if(p->getItem_byID("ticket") == NULL)
    {
        std::cout << "Couldn't find ticket.\n";
        return;
    }

    p->appendPrint("Du siehst deinen Zug einfahren. Du bewegst dich auf ihn zu, zeigst dein Ticket, der Schaffner musstert dich kurz und lässt dich dann eintreten. Du suchst dir einen freien Platz, legst dein Bündel auf den sitz neben dich und schläfst ein...\n $ Nach einem scheinbar endlos langem schlaf wachst du wieder in deinem Abteil auf. Das Abteil ist leer. Leer bist auf einen geheimnisvollen Begleiter: Parsen.");

    p->setRoom(p->getWorld()->getRooms()["compartment-a"]);

}

void CStandardContext::h_try(string& sIdentifier, CPlayer* p)
{
    if(sIdentifier == "1") h_try1(sIdentifier, p);
    if(sIdentifier == "2") h_try2(sIdentifier, p);
    if(sIdentifier == "3") h_try3(sIdentifier, p);
}
void CStandardContext::h_try1(string&, CPlayer* p)
{
    throw_event("go to neben", p);
    throw_event("go to toil", p);
    throw_event("go to mä", p);
    throw_event("talk to tick", p);
}
void CStandardContext::h_try2(string&, CPlayer* p)
{
    throw_event("go to vor", p);
    throw_event("go to neben", p);
    throw_event("go to eing", p);
    throw_event("go to gleise", p);
}
void CStandardContext::h_try3(string&, CPlayer* p)
{
    throw_event("go to neben", p);
    throw_event("go to toil", p);
    throw_event("go to frau", p);
}
