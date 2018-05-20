#include "Constant.h"

Constant::Constant(double value): value_(value){}

double Constant::eval(const map<string, double> &variables)
{
    return value_;
}
