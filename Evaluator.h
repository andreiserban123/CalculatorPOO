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
   /* double performOperation(double operand1, double operand2, char operation);
    double evaluateRPN(const std::string& rpnExpression);
    void evaluate(double operator1, double operator2, char token);*/

    double evaluateRPN(const std::string& rpnExpression);

    Evaluator operator++(int);
    Evaluator& operator++();
    bool operator>(Evaluator &e);
    double getResult();
    void setResult(double x);
    void printFinalResult();
    friend void operator<<(std::ostream& console, Evaluator& e);
    friend void operator>>(std::istream& console, Evaluator& e);
};

void operator<<(std::ostream& console, Evaluator& e);
void operator>>(std::istream& console, Evaluator& e);
