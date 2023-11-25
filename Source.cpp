#include <iostream>
#include <string>

using namespace std;

class Parser {
	char* expression;
public:
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
			delete[] this->expression;
			this->expression = new char[expr.length() + 1];
			strcpy_s(this->expression, expr.length() + 1, expr.c_str());
		}
	}
};

class Evaluator {
};

class Calculator {
	bool isRunning = false;
	static int noCalculators;
public:
	Calculator() {
		isRunning = true;
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
		string expression;
		cout << "Calculatorul stiintific. Introduceti o expresie sau 'exit' pentru a iesi." << endl;
		while (this->isRunning) {
			cout << "Expresie: ";
			getline(cin, expression);

			if (expression == "exit" || expression == "") {
				this->isRunning = false;
				break;
			}

			float result = 0;
			cout << "Rezultat: " << result << endl;
		}
	}
};

int Calculator::noCalculators = 0;

int main() {
	Calculator calc;
	calc.run();
}
