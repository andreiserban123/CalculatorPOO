#include "Calculator.h"
#include "Parser.h"
#include "CalculatorWithFile.h"

int main(int argc, char* argv[]) {
	if (argc == 2) {
		std::cout << "You entered the expression from argument" << std::endl;
		Parser p;
		std::string expression = argv[1];
		p.setExpression(expression);
		p.removeSpaces();
		p.processExpression();
	}
	else {
		bool flag = true;
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
			Calculator calc(1);
			calc.run();
		}
		else {
			std::cout << "Invalid choice" << std::endl;
		}
	}
}
