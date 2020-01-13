#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "func.hpp"


int main()
{
    std::string m_sPrint = "Hallo ich gehe morgen in das Kino.";

    srand(time(NULL));
    size_t num;
    std::vector<std::string> words = func::split(m_sPrint, " ");

    size_t highness=2;

    for(auto& word : words)
    {
        if(word.size() <= highness) 
            continue;
        size_t inc = word.size()-(highness-1);
        for(size_t i=0; i<word.size();)
        {
            i+=inc;
            if(!isalpha(word[i]))
                continue;

            num = rand() % word.size()-1;
            if(!isalpha(word[num]))
                continue;

            char x = word[i];
            word[i] = word[num];
            word[num] = x;
        }
    }

    m_sPrint="";
    for(auto word : words) {
        m_sPrint+=word + " ";
    }
    std::cout << m_sPrint << "\n";
}
