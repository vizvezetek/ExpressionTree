#include <iostream>
#include <cctype>
#include <map>
#include <string>
#include <stdexcept>


using namespace std;

enum TokenType{
    Const,
    Operat,
    Openp,
    Closep,
    Var
};

struct Token{
    string value;
    TokenType type;
};


class Tokenizer {
public:
    Tokenizer(const string &input):input_(input), current_(input_.begin())
    {
    }
    bool getNext(Token &token);
private:
    string input_;
    string::iterator current_;
};



bool Tokenizer::getNext(Token &token)
{
    token.value.clear();
	if(current_ == input_.end()) return false;

    if(*current_ =='(')
    {
    	token.type = Openp;
        ++current_;
    }
    else if(*current_ == ')')
    {
    	token.type = Closep;
        ++current_;
    }
    else if(*current_ == '+' || *current_ == '-' || *current_ == '*' || *current_ == '/')
    {
    	token.type = Operat;
        token.value.push_back(*current_);
        ++current_;
    }
    else if(isdigit(*current_))
    {
        token.type = Const;
        while(current_ != input_.end() && isdigit(*current_))
        {
            token.value.push_back(*current_);
            ++current_;		//iterátor léptetése
        }
    }
    else if(isalpha(*current_))
    {
      token.type = Var;
      while(current_ != input_.end() && isalpha(*current_))
      {
      	token.value.push_back(*current_);
        ++current_;		//iterátor léptetése
      }
    }
    return true;
}

class Expression{
	public:
		virtual double eval(const map<string, double> &variables) = 0;
};

class Constant: public Expression
{
    public:
		Constant(double value): value_(value){}
        virtual double eval(const map<string, double> &variables);
    private:
		double value_;
};

double Constant::eval(const map<string, double> &variables)
{
		return value_;
}

class Variable: public Expression
{
    public:
        Variable(const string & name): name_(name){}

        virtual double eval(const map<string, double> &variables);
    private:
            string name_;
};

double Variable::eval(const map<string, double> &variables)
{
    const map<string, double>::const_iterator i= variables.find(name_);
    if(i == variables.end())
    {
        throw runtime_error("Undefined variable: " + name_);
    }
    return i->second;
}

class Operator: public Expression
{
    public:
		Operator(const string & name,
             Expression *left,
             Expression *right): name_(name), left_(left), right_(right) {}

        virtual double eval(const map<string, double> &variables);
    private:
		string name_;
    Expression *left_;
    Expression *right_;
};

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


int main()
{

	Tokenizer tz("(2+3)");
    Token t;
    while(tz.getNext(t))
    {
        cout << t.value<< endl;
    }

    Constant *c = new Constant(2.0);
    Variable *v = new Variable("x");
    Expression *root = new Operator("+", c, v);

    map<string, double> variables;
    variables["x"] = 3.0;

    cout << root->eval(variables) << endl;


    cout << "asdasd" << endl;
    return 0;
}
