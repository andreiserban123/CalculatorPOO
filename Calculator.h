#pragma once
#include "Parser.h"
#include <iostream>

class Calculator {
private:
    const int id;
    bool isRunning;
    static int noCalculators;
    bool intermediateResults;

public:
    Calculator();
    Calculator(int id, bool intermediateResults);
    bool isValidExpression(const std::string& expression);
    int getId();
    virtual bool getIsRunning();
    void setIsRunning(bool isRunning);

    ~Calculator();

    virtual void run();
    static void printNumberOfCalcs();

    friend void operator>>(std::istream& console, Calculator& c);
    friend void operator<<(std::ostream& console, Calculator& c);

    bool operator!();
    explicit operator bool();
};

void operator>>(std::istream& console, Calculator& c);
void operator<<(std::ostream& console, Calculator& c);
