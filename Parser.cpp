#include "Parser.h"
#include "Evaluator.h"
#include <iostream>
#include <string>
#include <stack>
#include <sstream>


Parser::Parser() : expression(nullptr), outputToFile(false) {}

Parser::Parser(const std::string& expression)
{
    this->outputToFile = false;
    std::string result;
    int i;
    for (i = 0; i < expression.size(); i++)
    {
        if (!std::isspace(expression[i]))
        {
            result += expression[i];
        }
    }
    this->expression = new char[result.length() + 1];
    strcpy_s(this->expression, result.length() + 1, result.c_str());
}

Parser::Parser(bool outputToFile)
{
	this->outputToFile = outputToFile;
    this->expression = nullptr;
}

Parser::~Parser()
{
    if (expression != nullptr)
    {
        delete[] expression;
        this->expression = nullptr;
    }
}


void Parser::removeSpaces() {
    if (this->expression == nullptr)
        return;

    std::string expr(this->expression);

    expr.erase(std::remove_if(expr.begin(), expr.end(), ::isspace), expr.end());

    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '#' || expr[i] == '^' || expr[i] == '(' || expr[i] == ')' || expr[i] == '[' || expr[i] == ']' || expr[i] == '/' || expr[i] == '%')
        {
            expr.insert(i, " ");
            expr.insert(i + 2, " ");
            i += 2;
        }
    }

    delete[] this->expression;
    this->expression = new char[expr.length() + 1];
    strcpy_s(this->expression, expr.length() + 1, expr.c_str());
}

void Parser::processExpression() {
    if (expression != nullptr) {
        std::string expr = expression;

        Evaluator evaluator;

        std::string rpnExpression = infixToRPN(expr);

        for (int i = 0; i < rpnExpression.size(); i++) {
            if (rpnExpression[i] == '+' || rpnExpression[i] == '-' || rpnExpression[i] == '*' || rpnExpression[i] == '/' || rpnExpression[i] == '%' || rpnExpression[i] == '^' || rpnExpression[i] == '#')
            {
				rpnExpression.insert(i, " ");
				rpnExpression.insert(i + 2, " ");
				i += 2;
			}
        }

        double result = evaluator.evaluateRPN(rpnExpression);

        evaluator.setResult(result);
        if (this->outputToFile == false) {
            evaluator.printFinalResult();
        }
        else {
			evaluator.printFinalResultToFile();
        }
    }
}

Parser::Parser(const Parser& other)
{
    if (other.expression != nullptr)
    {
        this->outputToFile = other.outputToFile;
        expression = new char[std::strlen(other.expression) + 1];
        strcpy_s(expression, std::strlen(other.expression) + 1, other.expression);
    }
    else
    {
        expression = nullptr;
    }
}

Parser& Parser::operator=(const Parser& other)
{
    if (this == &other)
    {
        return *this;
    }

    if (other.expression != nullptr)
    {
        delete[] expression;
        expression = new char[std::strlen(other.expression) + 1];
        strcpy_s(expression, std::strlen(other.expression) + 1, other.expression);
    }

    return *this;
}

char* Parser::getExpression()
{
    if (expression != nullptr)
    {
        int length = std::strlen(expression);
        char* copy = new char[length + 1];
        strcpy_s(copy, length + 1, expression);
        return copy;
    }
    else
    {
        return nullptr;
    }
}

void Parser::setExpression(const std::string& expr) {
    if (!expr.empty()) {
        delete[] expression;
        expression = new char[expr.length() + 1];
        strcpy_s(expression, expr.length() + 1, expr.c_str());
    }
}


void operator>>(std::istream& console, Parser& p)
{
    std::cout << "Enter an expression: ";
    std::string g;
    console >> g;
    delete[] p.expression;
    p.expression = new char[g.size() + 1];
    strcpy_s(p.expression, g.size() + 1, g.c_str());
}

void operator<<(std::ostream& console, const Parser& p)
{

    if (p.expression != nullptr)
    {
        console << p.expression << std::endl;
    }
    else
    {
        console << "expresia este nula" << std::endl;
    }
}



char& Parser::operator[](int x)
{
    if (x >= 0 && x < std::strlen(this->expression)) {
        return this->expression[x];
    }
    else {
        throw std::exception("Invalid index");
    }
}

int Parser::operator+(Parser& p)
{
    if (expression != nullptr && p.expression != nullptr)
    {
        return std::strlen(expression) + std::strlen(p.expression);
    }
    return 0;
}

int Parser::operator+(int x)
{
    return std::strlen(this->expression) + x;
}

int operator+(int x, Parser& p)
{
    return p + x;
}



bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c=='^' || c=='#';
}

bool isOperand(char c) {
    return std::isalnum(c) || c == '.'; 
}

bool isOpeningParenthesis(char c) {
    return c == '(' || c == '[';
}

bool isClosingParenthesis(char c) {
    return c == ')' || c == ']';
}

int Parser::getPrecedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    return 0; 
}

std::string Parser::infixToRPN(const std::string& infixExpression) {
    std::string rpnExpression;
    std::stack<char> operatorStack;

    std::istringstream iss(infixExpression);
    std::string token;

    while (iss >> token) {
        char firstChar = token[0];

        if (isOperand(firstChar)) {
            rpnExpression += token + " ";
        }
        else if (isOperator(firstChar)) {
            while (!operatorStack.empty() && isOperator(operatorStack.top()) &&
                getPrecedence(operatorStack.top()) >= getPrecedence(firstChar)) {
                rpnExpression += operatorStack.top();
                rpnExpression += " ";
                operatorStack.pop();
            }
            operatorStack.push(firstChar);
        }
        else if (isOpeningParenthesis(firstChar)) {
            operatorStack.push(firstChar);
        }
        else if (isClosingParenthesis(firstChar)) {
            while (!operatorStack.empty() && !isOpeningParenthesis(operatorStack.top())) {
                rpnExpression += operatorStack.top(); 
                rpnExpression += " ";
                operatorStack.pop();
            }
            if (!operatorStack.empty() && isOpeningParenthesis(operatorStack.top())) {
                operatorStack.pop(); 
            }
            else {
                std::cerr << "Error: Mismatched parentheses." << std::endl;
                return ""; 
            }
        }
        else {
            std::cerr << "Error: Invalid character in expression." << std::endl;
            return ""; 
        }
    }

    while (!operatorStack.empty()) {
        if (isOpeningParenthesis(operatorStack.top()) || isClosingParenthesis(operatorStack.top())) {
            std::cerr << "Error: Mismatched parentheses." << std::endl;
            return ""; 
        }
        rpnExpression += operatorStack.top();
        operatorStack.pop();
    }

    return rpnExpression;
}