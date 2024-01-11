#include "Calculator.h"
#include "Parser.h"
#include "CalculatorWithFile.h"
#include <sstream>


int main(int argc, char* argv[]) {
	if (argc >= 2) {
		std::cout << "You entered the expression from argument" << std::endl;
		Parser p;
		std::string expression;
		for (int i = 1; i < argc; i++) {
			expression += argv[i];
			expression += " ";
		}
		p.setExpression(expression);
		p.removeSpaces();
		p.processExpression();
	}
	else {
		std::cout << "Do you want to read from file or from console? (f/c)" << std::endl;
		char choice;
		std::cin >> choice;
		if (choice == 'f') {
			std::cout << "Enter the name of the file: ";
			std::string fileName;
			std::cin >> fileName;
			CalculatorWithFile calc(1, fileName);
			calc.run();
		}
		else if (choice == 'c') {
			std::cout <<"Do you want to save intermediate results?(y/n)" << std::endl;
			char choice;
			std::cin >> choice;
			if (choice == 'y') {
				Calculator calc(1, true);
				calc.run();
			}
			else if (choice == 'n') {
				Calculator calc(1, false);
				calc.run();
			}
			else {
				std::cout << "Invalid choice" << std::endl;
			}
		}
		else {
			std::cout << "Invalid choice" << std::endl;
		}
	}
}
