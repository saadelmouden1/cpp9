#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <exception>

class RPN
{
    private:
        std::stack<double> _stack;
        void _executeStack(double(RPN::*f)(double, double));
        double _plus(double a,double b);
        double _minus(double a,double b);
        double _multiply(double a, double b);
        double _dvide(double a, double b);
    
    public:
        RPN();
        RPN(const std::string &input);
        RPN(const RPN &oth);
        RPN &operator=(const RPN &oth);
        ~RPN();

        double getResult() const;

        class invalidArgument : public std::runtime_error
		{
			public:
				explicit invalidArgument(const std::string& msg);
		};

		class emptyStack : public std::runtime_error
		{
			public:
				explicit emptyStack(const std::string& msg);
		};

		class divisionByZero : public std::runtime_error
		{
			public:
				explicit divisionByZero(const std::string& msg);
		};	


};


#endif