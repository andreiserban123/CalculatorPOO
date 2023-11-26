#pragma once
#include <iostream>
using namespace std;

class Evaluator {
	double result = 0;
	bool err = false;
public:
	Evaluator() {
		this->result = 0;
	}
	Evaluator(double result) {
		this->result = result;
	}

	bool getErr() {
		return this->err;
	}
	bool setErr(bool t) {
		this->err = t;
	}
	void evaluate(double operator1, double operator2, char token) {
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
					result = operator1 / operator2;
				}
				else {
					throw exception("Error: Division by 0");
				}
				break;
			default:
				cout << "Error: Unknown operator." << endl;
				err = true;
				return;
			}
		}
		catch (exception e) {
			cout << e.what();
			err = true;
		}
	}

	Evaluator operator++(int) {
		Evaluator copie = *this;
		this->result++;
		return copie;
	}
	Evaluator& operator++() {
		this->result++;
		return *this;
	}
	double getResult() {
		return this->result;
	}

	void setResult(int x) {
		this->result = x;
	}

	void printFinalResult() {
		if (!err)
			cout << "Result:" << result;
		cout << endl;
	}
	friend void operator<<(ostream& console, Evaluator& e);
	friend void operator>>(istream& console, Evaluator& e);
};

void operator<<(ostream& console, Evaluator& e) {
	console << e.result << endl;
}
void operator>>(istream& console, Evaluator& e) {
	console >> e.result;
}