#include <iostream>
#include <string>
#include "CStorage.h"
using namespace std;

enum ECommandType
{
    PRINT, INCR_LINE, DECR_LINE, QUIT
};

vector<ECommandType> translateCommand(string commandString)
{
    vector<ECommandType> commands;
    if(commandString == "p")
    {
        commands.push_back(PRINT);
    }
    if(commandString == "+")
    {
        commands.push_back(INCR_LINE);
    }
    if(commandString == "-")
    {
        commands.push_back(DECR_LINE);
    }
    if(commandString == "q")
    {
        commands.push_back(QUIT);
    }
    if(commandString == "pp")
    {
        commands.push_back(PRINT);
        commands.push_back(INCR_LINE);
        commands.push_back(PRINT);
    }

    return commands;
}

string prompt()
{
	string mode = "NORMAL";
	return mode + "> ";
}

int main()
{
	int lineNumber = 0;
	CStorage storage("main.cpp");

	string choice;
	while(true)
	{
		cout << prompt();
		cin >> choice;
        vector<ECommandType> c = translateCommand(choice);
        for(int i = 0; i < c.size(); i++)
        {
            if(c[i] == PRINT)
            {
                cout << storage.getLineAt(lineNumber)<< endl;
                continue;
            }
            if(c[i] == INCR_LINE)
            {
                lineNumber++;
                continue;
            }
            if(c[i] == DECR_LINE)
            {
                lineNumber--;
                continue;
            }
            if(c[i] == QUIT)
            {
                cout << "Goodbye!" << endl;
                return 0;
            }
        }
	}
	return 0;
}
