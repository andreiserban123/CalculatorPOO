#pragma once
#include <iostream>

class Evaluator {
private:
    double result;
    bool err;

public:
    Evaluator();
    Evaluator(double result);

    bool getErr();
    void setErr(bool t);
    void evaluate(double operator1, double operator2, char token);

    Evaluator operator++(int);
    Evaluator& operator++();
    double getResult();
    void setResult(int x);

    void printFinalResult();
    friend void operator<<(std::ostream& console, Evaluator& e);
    friend void operator>>(std::istream& console, Evaluator& e);
};

void operator<<(std::ostream& console, Evaluator& e);
void operator>>(std::istream& console, Evaluator& e);
