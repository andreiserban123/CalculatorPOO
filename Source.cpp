#include "Calculator.h"
#include "Parser.h"

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

		Calculator calc(1);
		calc.run();
	}
}
