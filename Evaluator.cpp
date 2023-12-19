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

double Evaluator::evaluateRPN(const std::string& rpnExpression) {
    std::stack<double> operandStack;

    std::istringstream iss(rpnExpression);
    std::string token;

    while (iss >> token) {
        if (token.empty()) continue;
        if (isdigit(token[0]) || (token.size() > 1 && isdigit(token[1]))) {
            operandStack.push(std::stod(token));
        }
        else {
            double operand2 = operandStack.top();
            operandStack.pop();

            double operand1 = operandStack.top();
            operandStack.pop();

            if (token == "+") {
                operandStack.push(operand1 + operand2);
            }
            else if (token == "-") {
                operandStack.push(operand1 - operand2);
            }
            else if (token == "*") {
                operandStack.push(operand1 * operand2);
            }
            else if (token == "/") {
                operandStack.push(operand1 / operand2);
            }
            else if (token == "^") {
                operandStack.push(std::pow(operand1, operand2));
            }
            else if (token == "#") {
                operandStack.push(std::pow(operand1, 1 / operand2));
            }
            else {
                // Handle other operators as needed
                std::cerr << "Error: Unknown operator:  " << token << std::endl;
                return 0.0;
            }
        }
    }

    // The result should be on the top of the stack
    if (!operandStack.empty()) {
      return operandStack.top();
    }
    else {
        throw std::exception("Error: Empty stack");
       return 0.0;
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
