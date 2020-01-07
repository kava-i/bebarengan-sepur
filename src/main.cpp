#include <iostream>
#include "CGame.hpp"

int main()
{
    CGame game;

    game.worldFactory();

    //First output
    std::cout << "Anna wakes up in her compartment.\n";

    for(;;)
    {
        std::string sInput;
        //Get player input
        std::cout << "> ";
        getline(std::cin, sInput);

        if(sInput == ":q")
            break;

        std::cout << game.play(sInput) << "\n";
    }


    std::cout << "Thank you for playing.\n";
}
