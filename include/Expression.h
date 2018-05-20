#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "Tokenizer.h"

using namespace std;

class Expression
{
    public:
        virtual double eval(const map<string, double> &variables) = 0;
};

#endif // EXPRESSION_H
