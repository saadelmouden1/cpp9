#include "RPN.hpp"

RPN::RPN()
{

}

RPN::RPN(const std::string &input)
{
    std::stringstream ss(input);
    std::string token;
    int num;


	while (std::getline(ss, token, ' '))
	{
        if (token.empty())
            continue;
		if ((token.length() == 1 && isdigit(token[0])) || (token.length() == 2 && token[0] == '-' && isdigit(token[1])))
		{
			std::stringstream(token) >> num;
			_stack.push(num);
		}
		else if (token == "+")
			_executeStack(&RPN::_plus);
		else if (token == "-")
			_executeStack(&RPN::_minus);
		else if (token == "*")
			_executeStack(&RPN::_multiply);
		else if (token == "/")
			_executeStack(&RPN::_dvide);
		else
			throw RPN::invalidArgument("Invalid argumentt: " + token);
	}
}



RPN::RPN(const RPN &oth)
{
	*this = oth;
}

RPN &RPN::operator=(const RPN &oth)
{
	if (this != &oth)
		_stack = oth._stack;
	return (*this);
}

RPN::~RPN()
{
}

RPN::invalidArgument::invalidArgument(const std::string& msg) : std::runtime_error(msg)
{
}

RPN::emptyStack::emptyStack(const std::string& msg) : std::runtime_error(msg)
{
}

RPN::divisionByZero::divisionByZero(const std::string& msg) : std::runtime_error(msg)
{
}


double RPN::getResult() const
{
    if(_stack.empty())
        throw RPN::emptyStack("Empty stack");
    else if(_stack.size() > 1)
        throw RPN::invalidArgument("Invalid argument");
    return (_stack.top());
}


void RPN::_executeStack(double (RPN::*f)(double, double))
{
    double a;
    double b;

    if(_stack.size() < 2)
        throw RPN::emptyStack("Empty stack");
    a = _stack.top();
    _stack.pop();
    b  =_stack.top();
    _stack.pop();
    _stack.push((this->*f)(a,b));
}

double RPN::_plus(double a, double b)
{
	return (b + a);
}

double RPN::_minus(double a, double b)
{
	return (b - a);
}

double RPN::_multiply(double a, double b)
{
	return (b * a);
}

double RPN::_dvide(double a, double b)
{
	if (a == 0)
		throw RPN::divisionByZero("Division by zero");
	return (b / a);
}