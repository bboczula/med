#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string prompt()
{
	string mode = "NORMAL";
	return mode + "> ";
}

int main()
{
	ifstream file("main.cpp");
	string choice;
	while(true)
	{
		cout << prompt();
		cin >> choice;
		if(choice == "q")
		{
			return 0;
		}
	}
	return 0;
}
