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

	Evaluator& operator++(int) {
		Evaluator copie = *this;
		this->result++;
		return copie;
	}
	double getResult() {
		return this->result;
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
	double* results = nullptr;
	int noResults = 0;
public:
	Parser() {
		this->expression = nullptr;
		this->results = nullptr;
		noResults = 0;
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
		noResults = 0;
		this->results = nullptr;
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

			string* vec = new string[expr.size()];
			
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
			Evaluator evaluator(stod(vec[0]));
			for (int i = 1; i < index; i++) {
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


class MyCalculator1 {
	const int id;
	bool isRunning = false;
	static int noCalculators;
public:
	MyCalculator1():id(0) {
		this->isRunning = false;
	}

	int getId() {
		return this->id;
	}

	MyCalculator1(int id): id(id){
		this->isRunning = true;
		MyCalculator1::noCalculators++;
	}

	bool getIsRunning() const {
		return this->isRunning;
	}

	void setIsRunning(bool isRunning) {
		this->isRunning = isRunning;
	}

	~MyCalculator1() {
		MyCalculator1::noCalculators--;
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
		cout << "Number of calculators is: " << MyCalculator1::noCalculators;
	}
};

int MyCalculator1::noCalculators = 0;



int main() {
	MyCalculator1 calc(1);
	calc.run();
}
