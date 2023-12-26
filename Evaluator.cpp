#include "Evaluator.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stack>
#include <fstream>

Evaluator::Evaluator() : result(0), err(false) {}

Evaluator::Evaluator(double result) : result(result), err(false) {}

bool Evaluator::getErr() {
    return err;
}

void Evaluator::setErr(bool t) {
	this->err = t;
}

void Evaluator::printFinalResultToFile()
{

    std::ofstream file;
    file.open("result.txt", std::ios::app);
    if (file.is_open()) {
        if (result == 0.0) {

            file << "Result: 0" << std::endl;
        }
        else {
			file << std::fixed << std::setprecision(4) << "Result: " << result << std::endl;
		}
		file.close();
	}
    else {
		std::cout << "Unable to open file" << std::endl;
	}

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
                std::cerr << "Error: Unknown operator:  " << token << std::endl;
                return 0.0;
            }
        }
    }

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
    if (!err) {
        if (result == 0.0) {
			std::cout << "Result: 0";
		}
        else {
			std::cout << std::fixed << std::setprecision(4) << "Result: " << result;
		}
    }
    std::cout << std::endl;
}

void operator<<(std::ostream& console, Evaluator& e) {
    console << e.result << std::endl;
}

void operator>>(std::istream& console, Evaluator& e) {
    console >> e.result;
}

void Evaluator::evaluate(double operand2, char token) {
    if (currentOperation != nullptr) {
        result = currentOperation->execute(result, operand2);
    }
    else {
        std::cerr << "Error: No valid operation set." << std::endl;
        err = true;
    }
}