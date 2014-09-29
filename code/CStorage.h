#ifndef C_STORAGE_H
#define C_STORAGE_H

#include <vector>
#include <fstream>
#include <iostream>
#include <string>

class CStorage : std::vector<std::string>
{
	void readFile(std::string name)
	{
		std::cout << "Reading file " << name << "..." << std::endl;
		std::ifstream file(name.c_str());
		std::string line;
		while(getline(file, line))
		{
			push_back(line);
		}
		file.close();
		std::cout << size() << " lines read successfully." << std::endl;
	}
public:
	CStorage(std::string filename)
	{
		readFile(filename);
	}
	std::string getLineAt(int lineNumber)
	{
        if(lineNumber < 0)
            std::cerr << "ERROR001: you're trying to fetch line that doesn't exist!" << std::endl;
        if(lineNumber >= size())
            std::cerr << "ERROR002: you're trygin to fech line out of bounds!" << std::endl;
        return operator[](lineNumber);
    }
    int getTotalNumberOfLines()
    {
        return size();
    }
};

#endif
