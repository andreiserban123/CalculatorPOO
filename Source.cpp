#include <iostream>
#include <string>
using namespace std;


class Expression {
private:
	string expression;
public:
	Expression(const string& expression) : expression(expression) {}

	// Metode pentru analiza expresiei și extragerea componentelor
	// Puteți adăuga aici funcții pentru manipularea expresiilor, cum ar fi extragerea operatorilor și operandelor.
};

class ExpressionEvaluator {
public:
	double evaluate(const string& expression) {
		Expression expr(expression);

		// Implementați aici evaluarea expresiei utilizând datele din clasa Expression
		// Această funcție poate să utilizeze o stivă pentru a gestiona prioritățile și operațiile matematice.



		return 0.0; // Rezultat temporar
	}
};

class Calculator {
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
	Calculator(bool isRunning)
	{
		this->isRunning = isRunning;
	}
	void run() {
		ExpressionEvaluator evaluator;
		string expression;

		cout << "Calculatorul stiintific. Introduceti o expresie sau 'exit' pentru a iesi." << endl;

		while (this->isRunning) {
			cout << "Expresie: ";
			getline(cin, expression);

			if (expression == "exit") {
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

