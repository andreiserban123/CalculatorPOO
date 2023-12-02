#include "Calculator.h"
#include  "Parser.h"
#include <iostream>

int Calculator::noCalculators = 0;

Calculator::Calculator() : id(0), isRunning(false) {}

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

void Calculator::run() {
    Parser p;
    std::string expression;
    std::cout << "==============================================" << std::endl;
    std::cout << "       Welcome to the Scientific Calculator    " << std::endl;
    std::cout << "==============================================" << std::endl;
    std::cout << "Instructions: Enter a mathematical expression" << std::endl;
    std::cout << "              Or type 'exit'/'enter' to quit the calculator" << std::endl;
    std::cout << "==============================================" << std::endl;

    while (isRunning) {
        std::cout << "Expression: ";
        std::getline(std::cin, expression);

        if (expression == "exit" || expression == "") {
            isRunning = false;
            break;
        }

        p.setExpression(expression);
        p.processExpression();
    }
}

void Calculator::printNumberOfCalcs() {
    std::cout << "Number of calculators is: " << Calculator::noCalculators;
}

void operator>>(std::istream& console, Calculator& c) {
    std::cout << "IsRunning or not ?:";
    console >> c.isRunning;
}

void operator<<(std::ostream& console, Calculator& c) {
    std::cout << "IS RUNNING: ";
    if (c.isRunning == true) {
        console << "It's true";
    }
    else {
        console << "It's false";
    }
}
