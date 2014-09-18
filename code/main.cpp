#include <iostream>
#include <string>
#include "CStorage.h"
using namespace std;

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
		if(choice == "p")
		{
			cout << storage.getLineAt(lineNumber)<< endl;
			continue;
		}
		if(choice == "+")
		{
			lineNumber++;
			continue;
		}
		if(choice == "-")
		{
			lineNumber--;
			continue;
		}
		if(choice == "q")
		{
			return 0;
		}
	}
	return 0;
}
