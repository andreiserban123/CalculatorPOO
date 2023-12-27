#include "CalculatorWithFile.h"
#include <fstream>

CalculatorWithFile::CalculatorWithFile()
{
		this->fileName = "";
}

CalculatorWithFile::CalculatorWithFile(int id, std::string fileName) : Calculator(id, false)
{
	this->fileName = fileName;
}

std::string CalculatorWithFile::getFileName()
{
	return std::string();
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
		Parser p(true);
		std::ofstream clearResults("result.txt", std::ios::trunc);
		clearResults.close();
		while (getline(file, line)) {
			bool isValid = Calculator::isValidExpression(line);
			if (!isValid) {
				std::ofstream results("result.txt", std::ios::app);
				results << line << " is invalid" << std::endl;
				results.close();
			}
			else {
				p.setExpression(line);
				p.removeSpaces();
				p.processExpression();
			}
			
		}
		file.close();
	}
		else {
		std::cout << "Unable to open file" << std::endl;
	}
}
