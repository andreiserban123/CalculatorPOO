#include "Calculator.h"
#include  "Parser.h"
#include <iostream>
#include <sstream>

int Calculator::noCalculators = 0;

Calculator::Calculator() : id(0), isRunning(false) {
    Calculator::noCalculators++;
}

Calculator::Calculator(int id) : id(id) {
    isRunning = true;
    Calculator::noCalculators++;
}

int Calculator::getId() {
    return id;
}

bool Calculator::getIsRunning() {
    return isRunning;
}

void Calculator::setIsRunning(bool isRunning) {
    this->isRunning = isRunning;
}

Calculator::~Calculator() {
    Calculator::noCalculators--;
}

bool isValidExpression(const std::string& expression) {
 std::istringstream iss(expression);
	std::string token;
	int countDots = 0;
    while (iss >> token) {
        for (int i = 0; i < token.size(); i++) {
            if (token[i] == '.') {
				countDots++;
			}
        }
        if (countDots > 1) {
            return false;
        }
        countDots = 0;
    }
    return true;
}

void Calculator::run() {
    Parser p;
    std::string expression;
    std::cout << "==============================================" << std::endl;
    std::cout << "       Welcome to the Scientific Calculator    " << std::endl;
    std::cout << "==============================================" << std::endl;
    std::cout << "Instructions: Enter a mathematical expression" << std::endl;
    std::cout << "              Or type 'exit'/'enter' to quit the calculator" << std::endl;
    std::cout << "==============================================" << std::endl;
    std::cin.get();
    while (isRunning) {
        std::cout << "Expression: ";
        std::getline(std::cin, expression);

        if (expression == "exit" || expression == "") {
            isRunning = false;
            break;
        }
            p.setExpression(expression);
            p.removeSpaces();
            if (isValidExpression(p.getExpression()) == true) {
                p.processExpression();
            }
            else {
				std::cerr << "Error: Invalid expression. prea multe puncte" << std::endl;
			}
    }
}

void Calculator::printNumberOfCalcs() {
    std::cout << "Number of calculators is: " << Calculator::noCalculators;
}

bool Calculator::operator!()
{
    return !this->isRunning;
}

Calculator::operator bool()
{
    return this->isRunning;
}

void operator>>(std::istream& console, Calculator& c) {
    std::cout << "IsRunning or not ?:";
    console >> c.isRunning;
}

void operator<<(std::ostream& console, Calculator& c) {
    std::cout << "IS RUNNING: ";
    if (c.isRunning == true) {
        console << "true";
    }
    else {
        console << "false";
    }
}
