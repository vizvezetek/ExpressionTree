#include <iostream>
#include <cctype>
#include <map>
#include <string>
#include <stdexcept>
#include <vector>
#include <stack>
#include <cstdlib>

#include "Tokenizer.h"
#include "Expression.h"
#include "Constant.h"
#include "Variable.h"
#include "Operator.h"


using namespace std;

int precedence(const Token &t)
{
    if(t.value == "+" || t.value == "-") return 1;
    if(t.value == "*" || t.value == "/") return 2;
    if(t.value == "^" ) return 3;
}

vector<Token> postfixExpr(const string &input)
{
    Tokenizer tz(input);
    Token t;
    stack<Token> s;
    vector<Token> result;
    while(tz.getNext(t))
    {
        if(t.type == Operat)
        {
			while(not s.empty() && precedence(s.top()) >= precedence(t))
            {
                result.push_back(s.top());
                s.pop();
            }
            s.push(t);
        }
        else if(t.type == Openp)
        {
            s.push(t);
        }
        else if(t.type == Closep)
        {
            while(not s.empty() && s.top().type != Openp)
            {
                result.push_back(s.top());
                s.pop();
            }
            s.pop();
        }
        else
        {
            result.push_back(t);
        }
    }
	while(not s.empty())
    {
        result.push_back(s.top());
        s.pop();
    }
  return result;
}

void inputpostfixevaluator(string inp){
    vector<Token> postfix = postfixExpr(inp);

        stack<Expression*> s;

        for(vector<Token>::iterator i = postfix.begin(); i != postfix.end(); ++i)
        {
            if(i->type == Operat)
            {
            Expression *right = s.top();
            s.pop();
            Expression *left = s.top();
            s.pop();
            s.push(new Operator(i->value, left, right));
            }
            else if(i->type == Const)
            {
                s.push(new Constant(strtod(i->value.c_str(), NULL)));
            }
            else if(i->type == Var)
            {
                s.push(new Variable(i->value));
            }
        }
        Expression *root = s.top();
        map<string, double> variables;
    //    variables["x"] = 12345.0;

        cout << root->to_string() << '=' << root->eval(variables) << endl << endl;
}

int main()
{
    string inp;
    string inp2;
    bool ok=false;

    do
    {
        cout << "Adj meg egy meg kifejezest!"<< endl ;
        cin >> inp;
        if(inp.length()==0) ok=false;
        else ok = true;

        inputpostfixevaluator(inp);

        cout << "Szeretnel tovabbi kifejezest megadni? (y/n)"<< endl ;
        cin >> inp2;
        if(inp2.compare("y")!=0){
            return 0;
        }

    }
    while (ok);

//    vector<Token> postfix = postfixExpr("2^3+(2+3)*4+5");

//    for(vector<Token>::iterator i = postfix.begin(); i != postfix.end(); ++i)
//    {
//        cout << i->value ;
//    }

    //----------------
//    cout << endl;
//    for(vector<Token>::iterator i = postfix.begin(); i != postfix.end(); ++i)
//    {
//        cout << i->type ;
//    }
    //-----------------



    return 0;
}
