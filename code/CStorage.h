#ifndef C_STORAGE_H
#define C_STORAGE_H

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

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
	std::string getLineAt(int lineNumber) throw(std::out_of_range)
	{
        if(lineNumber < 0)
            throw std::out_of_range("ERROR001: you're trying to fetch line that doesn't exist!");
        if(lineNumber >= size())
            throw std::out_of_range("ERROR002: you're trygin to fech line out of bounds!");
        return operator[](lineNumber);
    }
    int getTotalNumberOfLines()
    {
        return size();
    }
};

#endif
