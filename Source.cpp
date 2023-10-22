#include <iostream>
#include <string>
using namespace std;


class Expression {
public:
	Expression(const string& expression) : expression(expression) {}

	// Metode pentru analiza expresiei și extragerea componentelor
	// Puteți adăuga aici funcții pentru manipularea expresiilor, cum ar fi extragerea operatorilor și operandelor.

private:
	string expression;
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
public:
	Calculator()
	{

	}
	void run() {
		ExpressionEvaluator evaluator;
		string expression;

		cout << "Calculatorul stiintific. Introduceti o expresie sau 'exit' pentru a iesi." << endl;

		while (true) {
			cout << "Expresie: ";
			getline(cin, expression);

			if (expression == "exit") {
				cout << "La revedere!" << endl;
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

