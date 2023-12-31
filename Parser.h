#pragma once
#include <string>

class Parser {
private:
    char* expression = nullptr;
    bool outputToFile = false;
    bool saveIntermediateResults = false;
    bool resultSaved = false;
public:
    Parser();
    Parser(const std::string& expression);
    Parser(bool outputToFile);
    ~Parser();
    bool getResultsSaved();
    void removeSpaces();
    void processExpression();

    void setIntermediateResults(bool saveIntermediateResults);
    void readIntermediateResult(double& prev);
    Parser(const Parser& other);
    Parser& operator=(const Parser& other);

    char* getExpression();
    void setExpression(const std::string& expr);

    friend void operator>>(std::istream& console, Parser& p);
    friend void operator<<(std::ostream& console, const Parser& p);

    char& operator[](int x);
    int operator+(Parser& p);
    int operator+(int x);
    int getPrecedence(char op);
    std::string infixToRPN(const std::string& infixExpression);
};
