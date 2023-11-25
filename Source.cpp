#include <iostream>
#include <string>

using namespace std;

class Evaluator {
	float result = 0;
public:
	Evaluator() {
		this->result = 0;
	}
	Evaluator(float result) {
		this->result = result;
	}
	void evaluate(float operator1, float operator2, char token) {
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
		case '/':
			if (operator2 != 0) {
				result = operator1 / operator2;
			}
			else {
				cout << "Error: Division by zero." << endl;
				return;  
			}
			break;
		default:
			cout << "Error: Unknown operator." << endl;
			return; 
		}
	}

	Evaluator& operator++(int) {
		Evaluator copie = *this;
		this->result++;
		return copie;
	}
	float getResult() {
		return this->result;
	}

	void printFinalResult()  {
		cout << "Final Result: " << getResult() << endl;
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

class Parser {
	char* expression = nullptr;
	double* results = nullptr;
public:
	Parser() {
		this->expression = nullptr;
		this->results = nullptr;
	} 
	Parser(const string& expression) {
		string result;
		for (char c : expression) {
			if (!isspace(c)) {
				result += c;
			}
		}
		this->expression = new char[result.length() + 1];
		strcpy_s(this->expression, result.length() + 1, result.c_str());
	}

	~Parser() {
		if (this->expression != nullptr)
			delete[] this->expression;
		delete[] this->results;
	}

	void processExpression() {
		if (this->expression != nullptr) {
			
			string expr = this->expression;
			int startPos, endPos, index;
			startPos = endPos = index = 0;
			char oper;

			string vec[100];
			
			for (int i = 0; i < expr.size(); i++) {
				if ((!isdigit(expr[i])) && expr[i]!= '.' ) {
					oper = expr[i];
					endPos = i - startPos;  
					vec[index++] = expr.substr(startPos, endPos);
					vec[index++] = oper;
					startPos = i + 1;  
				}
			}

			if (startPos < expr.size()) {
				vec[index++] = expr.substr(startPos);
			}
			Evaluator evaluator(stof(vec[0]));
			for (int i = 1; i < index; i++) {
				if (!isdigit(vec[i][0])) {
					
					float operand2 = stof(vec[i + 1]);
					char token = vec[i][0];
					evaluator.evaluate(evaluator.getResult(), operand2, token);
				}
			}
			evaluator.printFinalResult();
		}
	}


	Parser(const Parser& other) {
		this->expression = new char[strlen(other.expression) + 1];
		strcpy_s(this->expression, strlen(other.expression) + 1, other.expression);
	}

	Parser& operator=(const Parser& other) {
		if (this == &other) {
			return *this;
		}

		if (other.expression != nullptr) {
			delete[] expression;
			this->expression = new char[strlen(other.expression) + 1];
			strcpy_s(this->expression, strlen(other.expression) + 1, other.expression);
		}
		return *this;
	}

	string getExpression() {
		if (this->expression != nullptr) {
			return this->expression;
		}
		return "";
	}

	void setExpression(const string& expr) {
		if (!expr.empty()) {
			string result;
			for (char c : expr) {
				if (!isspace(c)) {
					result += c;
				}
			}
			delete[] this->expression;
			this->expression = new char[result.length() + 1];
			strcpy_s(this->expression, result.length() + 1, result.c_str());
		}
	}
};


class Calculator {
	bool isRunning = false;
	static int noCalculators;
public:
	Calculator(){
		this->isRunning = true;
		Calculator::noCalculators++;
	}

	bool getIsRunning() const {
		return this->isRunning;
	}

	void setIsRunning(bool isRunning) {
		this->isRunning = isRunning;
	}

	~Calculator() {
		Calculator::noCalculators--;
	}
	void run() {
		Parser p;
		string expression;
		cout << "==============================================" << endl;
		cout << "       Welcome to the Scientific Calculator    " << endl;
		cout << "==============================================" << endl;
		cout << "Instructions: Enter a mathematical expression" << endl;
		cout << "              Or type 'exit'/'enter' to quit the calculator" << endl;
		cout << "==============================================" << endl;

		while (this->isRunning) {
			cout << "Expression: ";
			getline(cin, expression);

			if (expression == "exit" || expression == "") {
				this->isRunning = false;
				break;
			}

			p.setExpression(expression);
			p.processExpression();
		}
	}

	static void printNumberOfCalcs() {
		cout << "Number of calculators is: " << Calculator::noCalculators;
	}
};

int Calculator::noCalculators = 0;

int main() {
	Calculator calc;
	calc.run();
}
