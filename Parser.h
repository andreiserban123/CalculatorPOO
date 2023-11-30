// Parser.h
#pragma once
#include <string>

class Parser {
private:
    char* expression;

public:
    Parser();
    Parser(const std::string& expression);
    ~Parser();

    void removeSpaces(std::string expr, std::string* vec, int& index);
    void processExpression();

    Parser(const Parser& other);
    Parser& operator=(const Parser& other);

    char* getExpression();
    void setExpression(const std::string& expr);

    friend void operator>>(std::istream& console, Parser& p);

    bool operator>(int x);
    int operator+(Parser& p);
};
