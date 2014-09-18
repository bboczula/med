#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class CStorage
{
	vector<string> storage;
	int totalNumberOfLines;
	void readFile(string name)
	{
		cout << "Reading file " << name << "..." << endl;
		ifstream file(name.c_str());
		string line;
		while(getline(file, line))
		{
			storage.push_back(line);
			totalNumberOfLines++;
		}
		file.close();
		cout << totalNumberOfLines << " lines read successfully." << endl;
	}
public:
	CStorage(string filename)
	{
		totalNumberOfLines = 0;
		readFile(filename);
	}
	string getLineAt(int lineNumber)
	{
		return storage[lineNumber];
	}
};

string prompt()
{
	string mode = "NORMAL";
	return mode + "> ";
}


int main()
{
	CStorage storage("main.cpp");

	int lineNumber = 0;
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
