#pragma once

class Operation {
public:
    virtual ~Operation() = default;
    virtual double execute(double operand1, double operand2) const = 0;
};
