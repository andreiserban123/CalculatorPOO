// Parser.cpp
#include "Parser.h"
#include "Evaluator.h"
#include <iostream>
#include <string>

Parser::Parser() : expression(nullptr) {}

Parser::Parser(const std::string& expression) {
    std::string result;
    for (char c : expression) {
        if (!std::isspace(c)) {
            result += c;
        }
    }
    this->expression = new char[result.length() + 1];
    strcpy_s(this->expression, result.length() + 1, result.c_str());
}

Parser::~Parser() {
    if (expression != nullptr)
        delete[] expression;
}

void Parser::removeSpaces(std::string expr, std::string* vec, int& index) {
    int startPos, endPos;
    startPos = endPos = index = 0;
    char oper;
    for (int i = 0; i < expr.size(); i++) {
        if ((!std::isdigit(expr[i])) && expr[i] != '.') {
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
}

void Parser::processExpression() {
    if (expression != nullptr) {
        std::string expr = expression;
        std::string* vec = new std::string[expr.size()];
        int index = 0;
        removeSpaces(expr, vec, index);

        Evaluator evaluator(std::stod(vec[0]));
        for (int i = 1; i < index; i++) {
            if (!std::isdigit(vec[i][0])) {
                double operand2 = std::stod(vec[i + 1]);
                char token = vec[i][0];
                evaluator.evaluate(evaluator.getResult(), operand2, token);
            }
        }
        evaluator.printFinalResult();
        delete[] vec;
    }
}

Parser::Parser(const Parser& other) {
    if (other.expression != nullptr) {
        expression = new char[std::strlen(other.expression) + 1];
        strcpy_s(expression, std::strlen(other.expression) + 1, other.expression);
    }
    else {
        expression = nullptr;
    }
}

Parser& Parser::operator=(const Parser& other) {
    if (this == &other) {
        return *this;
    }

    if (other.expression != nullptr) {
        delete[] expression;
        expression = new char[std::strlen(other.expression) + 1];
        strcpy_s(expression, std::strlen(other.expression) + 1, other.expression);
    }
    else {
        expression = nullptr;
    }
    return *this;
}

char* Parser::getExpression() {
    if (expression != nullptr) {
        int length = std::strlen(expression);
        char* copy = new char[length + 1];
        strcpy_s(copy, length + 1,expression);
        return copy;
    }
    else {
        return nullptr;
    }
}

void Parser::setExpression(const std::string& expr) {
    if (!expr.empty()) {
        std::string result;
        for (char c : expr) {
            if (!std::isspace(c)) {
                result += c;
            }
        }
        delete[] expression;
        expression = new char[result.length() + 1];
        strcpy_s(expression, result.length() + 1, result.c_str());
    }
}

void operator>>(std::istream& console, Parser& p) {
    std::cout << "Enter an expression: ";
    std::string g;
    console >> g;
    delete[] p.expression;
    p.expression = new char[g.size() + 1];
    strcpy_s(p.expression, g.size() + 1, g.c_str());
}

bool Parser::operator>(int x) {
    if (expression != nullptr)
        return std::strlen(expression) > x;
    return false;
}

int Parser::operator+(Parser& p) {
    if (expression != nullptr && p.expression != nullptr) {
        return std::strlen(expression) + std::strlen(p.expression);
    }
    return 0;
}
