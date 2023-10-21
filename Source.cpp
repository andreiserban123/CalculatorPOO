// CalculatorPOO.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;


class Expresie
{
private:
	char* input;
};

int main()
{
	string v;
	while (cin >> v) 
	{
		if (v == "exit")
		{
			return 0;
		}
		cout << v << endl;
	}
}

