#include <iostream>
#include "CGame.hpp"

int main()
{
    CGame game;

    std::string sName = "anna-bronec";

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
        else if(sInput == "change character")
        {
            std::cout << "Who do you want to play? (Anna, Jan) \n> ";
            getline(std::cin, sName);
            if(sName == "Anna") sName = "anna-bronec";
            if(sName == "Jan")  sName = "jan-van-dick";
            std::cout << "\n";
            continue;
        }


        std::string sOutput = game.play(sInput, sName);

        for(auto i=0; i<sOutput.length(); i++)
        {
            if(sOutput[i] != '$') std::cout << sOutput[i];
            else {
                std::cout << "Continue... ";
                int c=getchar();
            }
        }

        std::cout << "\n";
        
    }


    std::cout << "Thank you for playing.\n";
}
