#ifndef CDIALOG_H
#define CDIALOG_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

using std::string;
using std::map;
using std::vector;

class CDState;

struct SDialog {
    string sName;
    map<string, CDState*> states;
};

struct SDOption {
    string sText;
    string sTarget;
};

class CDState {
private:
    string m_sText;
    string m_sFunction;
    vector<string> m_alternativeTexts;    

    //Map of options 
    typedef std::map<int, SDOption> dialogoptions;
    dialogoptions m_options;

    //Referenc to the complete dialog
    SDialog* m_dialog;

    //Static map f all state-functions
    static std::map<string, string (CDState::*)()> m_functions;

public:
    CDState(string sText, string function, vector<string> altTexts, dialogoptions states, SDialog* dia);

    // *** GETTER *** // 
    string getText();
    dialogoptions& getOptions();

    // *** SETTER *** //
    void setText(size_t text);

    static void initializeFunctions();
    string callState();

    // *** functions *** //
    string standard();
    string parsen1();

    void changeStateText(string sStateID, size_t text);
    void addDialogOption(string sStateID, size_t optID);
    void deleteDialogOption(string sStateID, size_t optID);


    size_t numOptions();
};
#endif 
