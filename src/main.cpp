#include <iostream>
#include "CGame.hpp"
#include "JanGeschenk/Webconsole.hpp"
#include "JanGeschenk/Webgame.hpp"
    
CGame game;

class WebserverGame
{
    private:
        Webconsole *_cout;
	std::string _name;
	std::string _password;
	std::string _id;
    public:
	WebserverGame(Webconsole *cout)
	{
	    _name = "";
	    _password = "";
	    _id = "";
	    _cout = cout;
	    _cout->write("Name: ");
	    _cout->flush();
	}

	void onmessage(std::string sInput)
        {
	    if(_name=="")
	    {
		_name=sInput;
	        if(_name=="")
		{
		    _cout->write("\nName: ");
		    _cout->flush();
		    return;
		}
		_cout->write("\nPassword: ");
		_cout->flush();
		return;
	    }

	    if(_password=="")
	    {
		_password = sInput;
		if(_password=="")
		{
		    _cout->write("\nPassword: ");
		    _cout->flush();
		    return;
		}
		_id = game.checkLogin(_name,_password);
		if(_id=="")
		{
		    _name = "";
		    _password = "";
		    _cout->write(color::red, "Invalid Login please try again!",color::white, "\n\nName: ");
		    _cout->flush();
		    return;
		}
		sInput = "show rooms";
	    } 

	    

	    std::string sName = "anna-bronec";
	    if(sInput == ":q")
	    {
		_cout->write("Thanks for playing\n");
		return;
	    }
	    else if(sInput == "change character")
	    {
	        _cout->write("Who do you want to play? (Anna, Jan)");
		return;
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
