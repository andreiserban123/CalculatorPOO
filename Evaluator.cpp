#include "Evaluator.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stack>

Evaluator::Evaluator() : result(0), err(false) {}

Evaluator::Evaluator(double result) : result(result), err(false) {}

bool Evaluator::getErr() {
    return err;
}

void Evaluator::setErr(bool t) {
	this->err = t;
}

double Evaluator::performOperation(double operand1, double operand2, char operation) {
    switch (operation) {
    case '+':
        return operand1 + operand2;
    case '-':
        return operand1 - operand2;
    case '*':
        return operand1 * operand2;
    case '/':
        if (operand2 != 0) {
            return operand1 / operand2;
        }
        else {
            std::cerr << "Error: Division by 0." << std::endl;
            err = true;
            return 0;
        }
    case '%':
        return int(operand1) % int(operand2);
    case '#':
        if (operand1 >= 0 && operand2 > 0) {
            return pow(operand1, 1.0 / operand2);
        }
        else {
            std::cerr << "Error: Invalid radical expression." << std::endl;
            err = true;
            return 0;
        }
    case '^':
        return pow(operand1, operand2);
    default:
        std::cerr << "Error: Unknown operator." << std::endl;
        err = true;
        return 0;
    }
}

double stringToDouble(const std::string& str) {
    std::istringstream iss(str);
    double result;
    iss >> result;
    return result;
}

double Evaluator::evaluateRPN(const std::string& rpnExpression) {
    std::stack<double> operandStack;

    std::istringstream iss(rpnExpression);
    std::string token;
    while (iss >> token) {  
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            operandStack.push(stringToDouble(token));
        }
        else {
            if (token.length() == 1 && !std::isalnum(token[0])) {
                // It's an operator
                if (operandStack.size() < 2) {
                    std::cerr << "Error: Insufficient operands for operator " << token << std::endl;
                    err = true;
                    return 0;
                }

                double operand2 = operandStack.top();
                operandStack.pop();
                double operand1 = operandStack.top();
                operandStack.pop();

                double result = performOperation(operand1, operand2, token[0]);
                operandStack.push(result);
            }
            else {
                std::cerr << "Error: Invalid token in RPN expression: " << token << std::endl;
                err = true;
                return 0;
            }
        }
    }

    if (operandStack.size() != 1) {
        std::cerr << "Error: Invalid RPN expression" << std::endl;
        err = true;
        return 0;
    }

    return operandStack.top();
}


void Evaluator::evaluate(double operand1, double operand2, char token) {
    try {
        result = performOperation(operand1, operand2, token);
    }
    catch (std::exception& e) {
        std::cerr << e.what();
        err = true;
    }
}

Evaluator Evaluator::operator++(int) {
    Evaluator copie = *this;
    result++;
    return copie;
}

Evaluator& Evaluator::operator++() {
    result++;
    return *this;
}

bool Evaluator::operator>(Evaluator& e)
{
	if (this->result > e.result) {
		return true;
	}
	else {
		return false;
	}
}

double Evaluator::getResult() {
    return result;
}

void Evaluator::setResult(double x) {
    result = x;
}

void Evaluator::printFinalResult() {
    if (!err)
        std::cout << std::fixed << std::setprecision(4) << "Result:" << result;
    std::cout << std::endl;
}

void operator<<(std::ostream& console, Evaluator& e) {
    console << e.result << std::endl;
}

void operator>>(std::istream& console, Evaluator& e) {
    console >> e.result;
}
