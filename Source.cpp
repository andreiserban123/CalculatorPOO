#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;


class Expression 
{
private:
	char*expression;
public:
	Expression(const string& expression)  
	{
		string result;
		for (char c : expression) {
			if (!isspace(c)) {
				result += c;
			}
		}
		this->expression = new char[result.length() + 1];
		strcpy(this->expression, result.c_str());
	}

	~Expression() {
		if(this->expression!=nullptr)
		delete[] this->expression;
	}

	Expression(const Expression& other) {
		this->expression = new char[strlen(other.expression) + 1];
		strcpy(this->expression, other.expression);
	}

	Expression& operator=(const Expression& other) 
	{
		if (this == &other) 
		{
			return *this;
		}
		delete[] expression;
		
		this->expression = new char[strlen(other.expression) + 1];
		
		strcpy(this->expression, other.expression);
		
		return *this;
	}
};


class ExpressionEvaluator 
{
public:
	double evaluate(const string& expression)
	{
		Expression expr(expression);
		return 0.0;
	}
};

class Calculator 
{
private:
	bool isRunning;
public:

	bool getIsRunning()
	{
		return this->isRunning;
	}

	void setIsRunning(bool isRunning)
	{
		this->isRunning = isRunning;
	}
	Calculator()
	{
		this->isRunning = true;
	}
	void run() {
		ExpressionEvaluator evaluator;
		string expression;

		cout << "Calculatorul stiintific. Introduceti o expresie sau 'exit' pentru a iesi." << endl;

		while (this->isRunning) {
			cout << "Expresie: ";
			getline(cin, expression);

			if (expression == "exit" || expression == "") {
				this->isRunning = false;
				break;
			}
			double result = evaluator.evaluate(expression);
			cout << "Rezultat: " << result << endl;
		}
	}
};

int main()
{
	Calculator calc;
	calc.run();
}

