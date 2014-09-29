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
	void readFile(string name)
	{
		cout << "Reading file " << name << "..." << endl;
		ifstream file(name.c_str());
		string line;
		while(getline(file, line))
		{
			storage.push_back(line);
		}
		file.close();
		cout << storage.size() << " lines read successfully." << endl;
	}
public:
	CStorage(string filename)
	{
		readFile(filename);
	}
	string getLineAt(int lineNumber)
	{
        if(lineNumber < 0)
            cerr << "ERROR001: you're trying to fetch line that doesn't exist!" << endl;
        if(lineNumber >= storage.size())
            cerr << "ERROR002: you're trygin to fech line out of bounds!" << endl;
		return storage[lineNumber];
	}
    int getTotalNumberOfLines()
    {
        return storage.size();
    }
};

#endif
