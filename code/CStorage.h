#ifndef C_STORAGE_H
#define C_STORAGE_H

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
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

#endif