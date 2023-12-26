#pragma once
#include "Operation.h"

class AdditionOperation : public Operation {
public:
    double execute(double operand1, double operand2) const override;
};