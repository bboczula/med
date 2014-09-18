#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	ifstream file("main.cpp");
	string mode = "NORMAL";
	string prompt = mode + "> ";
	string line;
	while(true)
	{
		cout << prompt;
		cin >> line;
		if(line == "q")
		{
			return 0;
		}
	}
	return 0;
}
