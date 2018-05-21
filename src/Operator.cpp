#include "Operator.h"
#include <sstream>

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


string Operator::to_string()
{
    stringstream s;
    s<<left_->to_string() << name_ << right_->to_string();
    return s.str();
}
