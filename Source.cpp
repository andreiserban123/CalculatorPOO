#include <iostream>
#include <string>

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
	Evaluator& operator++(){
		this->result++;
		return *this;
	}
	double getResult() {
		return this->result;
	}

	void setResult(int x) {
		this->result = x;
	}

	void printFinalResult()  {
		if(!err)
		cout<<"Result:" << result;
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

class Parser {
	char* expression = nullptr;
public:
	Parser() {
		this->expression = nullptr;
		
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
	}

	void removeSpaces(string expr, string *vec) {
		int startPos, endPos, index;
		startPos = endPos = index = 0;
		char oper;
		for (int i = 0; i < expr.size(); i++) {
			if ((!isdigit(expr[i])) && expr[i] != '.') {
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
	}

	void processExpression() {
		if (this->expression != nullptr) {
			
			string expr = this->expression;
			string* vec = new string[expr.size()];
			removeSpaces(expr, vec);
			Evaluator evaluator(stod(vec[0]));
			for (int i = 1; i < vec->size(); i++) {
				if (!isdigit(vec[i][0])) {
					
					double operand2 = stod(vec[i + 1]);
					char token = vec[i][0];
					evaluator.evaluate(evaluator.getResult(), operand2, token);
				}
			}
			evaluator.printFinalResult();
			delete[] vec;
		}
	}


	Parser(const Parser& other) {
		if (other.expression != nullptr) {
			this->expression = new char[strlen(other.expression) + 1];
			strcpy_s(this->expression, strlen(other.expression) + 1, other.expression);
		}
		else {
			this->expression = nullptr;
		}
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
		else {
			this->expression = nullptr;
		}
		return *this;
	}

	char* getExpression() {
		if (this->expression != nullptr) {
			int length = strlen(this->expression);

			char* copy = new char[length + 1];

			strcpy_s(copy, length + 1, this->expression);

			return copy;
		}
		else {
			return nullptr;
		}
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
	friend void operator>>(istream& console, Parser& p);

	bool operator>(int x) {
		if(this->expression!=nullptr)
		return strlen(this->expression) > x;
		return false;
	}

	int operator+(Parser& p) {
		if (this->expression != nullptr && p.expression != nullptr) {
			return strlen(this->expression) + strlen(p.expression);
		}
		return 0;
	}

};

bool operator>(int x, Parser& p) {
	if(p.getExpression()!=nullptr)
	return strlen(p.getExpression()) > x;
	return false;
}

void operator>>(istream& console, Parser& p) {
	cout << "Enter an expression: ";
	string g;
	console >> g;
	delete[] p.expression;
	p.expression = new char[g.size() + 1];
	strcpy_s(p.expression, g.size() + 1, g.c_str());
}
void operator << (ostream& console, Parser& p) {
	console << p.getExpression();
}



class Calculator {
	const int id;
	bool isRunning = false;
	static int noCalculators;
public:
	Calculator():id(0) {
		this->isRunning = false;
	}

	int getId() {
		return this->id;
	}

	Calculator(int id): id(id){
		this->isRunning = true;
		Calculator::noCalculators++;
	}

	bool getIsRunning() {
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
	friend void operator>>(istream& console, Calculator& c);
	friend void operator<<(ostream& console, Calculator& c);

	bool operator!() {
		return !this->isRunning;
	}
	explicit operator bool() {
		return this->isRunning;
	}
};

void operator>>(istream & console, Calculator &c) {
	cout << "IsRunning or not ?:";
	console >> c.isRunning;
}

void operator<<(ostream& console, Calculator& c) {
	cout << "IS RUNNING: ";
	if (c.isRunning == true) {
		console << "It's true";
	}
	else {
		console << "It's false";
	}
}

int Calculator::noCalculators = 0;


int main() {
	Calculator calc(1);
	calc.run();

}
