#pragma once
#include "Calculator.h"

class CalculatorWithFile: public Calculator {
	std::string fileName;
public:
	CalculatorWithFile();
	CalculatorWithFile(int id, std::string fileName);
	std::string getFileName();
	void setFileName(std::string fileName);
	void run() override;
};