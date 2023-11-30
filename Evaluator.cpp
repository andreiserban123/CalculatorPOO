// Evaluator.cpp
#include "Evaluator.h"
#include <iostream>

Evaluator::Evaluator() : result(0), err(false) {}

Evaluator::Evaluator(double result) : result(result), err(false) {}

bool Evaluator::getErr() {
    return err;
}

void Evaluator::setErr(bool t) {
	this->err = t;
}

void Evaluator::evaluate(double operator1, double operator2, char token) {
	try {
		switch (token) {
		case '+':
			result = operator1 + operator2;
			break;
		case '-':
			result = operator1 - operator2;
			break;
		case '*':
			result = operator1 * operator2;
			break;
		case '%':
			result = (int)operator1 % (int)operator2;
			break;
		case '/':
			if (operator2 != 0) {
				result = (double)operator1 / (double)operator2;
			}
			else {
				throw std::exception("Error: Division by 0");
			}
			break;
		default:
			std::cout << "Error: Unknown operator." << std::endl;
			err = true;
			return;
		}
	}
	catch (std::exception e) {
		std::cout << e.what();
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

double Evaluator::getResult() {
    return result;
}

void Evaluator::setResult(int x) {
    result = x;
}

void Evaluator::printFinalResult() {
    if (!err)
        std::cout << "Result:" << result;
    std::cout << std::endl;
}

void operator<<(std::ostream& console, Evaluator& e) {
    console << e.result << std::endl;
}

void operator>>(std::istream& console, Evaluator& e) {
    console >> e.result;
}
