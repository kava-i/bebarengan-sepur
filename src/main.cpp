#include <iostream>
#include "CGame.hpp"
#include "JanGeschenk/Webconsole.hpp"
#include "JanGeschenk/Webgame.hpp"
    
CGame game;

class WebserverGame
{
    private:
        Webconsole *_cout;
    public:
	WebserverGame(Webconsole *cout)
	{
	    _cout = cout;
	    _cout->write("Anna wakes up in her compartment.\n");
	    _cout->flush();
	}

	void onmessage(std::string sInput)
        {
	     std::string sName = "anna-bronec";
	    if(sInput == ":q")
	    {
		_cout->write("Thanks for playing\n");
	    }
	    else if(sInput == "change character")
	    {
	        _cout->write("Who do you want to play? (Anna, Jan)");
	    }


	    std::string sOutput = game.play(sInput, sName);
	    _cout->write(sOutput);
	    _cout->flush();
	}
};

int main()
{
    Webgame<WebserverGame> gl;
    gl.run();
}
