#include "CalculatorWithFile.h"
#include <fstream>

CalculatorWithFile::CalculatorWithFile()
{
	this->fileName = "";
}

CalculatorWithFile::CalculatorWithFile(int id, std::string fileName) : Calculator(id)
{
	this->fileName = fileName;
}


std::string CalculatorWithFile::getFileName()
{
	return this->fileName;
}

void CalculatorWithFile::setFileName(std::string fileName)
{
		this->fileName = fileName;
}

void CalculatorWithFile::run()
{
		std::ifstream file(this->fileName);
		if (file.is_open()) {
		std::string line;
		while (getline(file, line)) {
			Parser p;
			p.setExpression(line);
			p.removeSpaces();
			p.processExpression();
		}
		file.close();
	}
		else {
		std::cout << "Unable to open file" << std::endl;
	}
}
