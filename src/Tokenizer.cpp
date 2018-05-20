#include "Tokenizer.h"

Tokenizer::Tokenizer(const string &input):input_(input), current_(input_.begin())
{
}

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
