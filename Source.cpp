#include "Calculator.h"

int main(int argc, char* argv[]) {
	if (argc >= 2) {
        std::string expression;
        for (int i = 1; i < argc; ++i) {
            expression += argv[i];
        }
		std::cout << expression << std::endl;
	}
	else {
		Calculator calc(1);
		calc.run();
	}
}
