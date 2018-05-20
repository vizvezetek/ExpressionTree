#include "Operator.h"

Operator::Operator(const string & name,
                    Expression *left,
                    Expression *right): name_(name), left_(left), right_(right) {}

double Operator::eval(const map<string, double> &variables)
{
    if(name_ == "+")
    {
        return left_->eval(variables) + right_->eval(variables);
    }
    else if(name_ == "-")
    {
        return left_->eval(variables) - right_->eval(variables);
    }
    else if(name_ == "*")
    {
  		return left_->eval(variables) * right_->eval(variables);
    }
    else if(name_ == "/")
    {
  		return left_->eval(variables) / right_->eval(variables);
    }
}
