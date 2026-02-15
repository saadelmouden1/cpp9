#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <exception>
#include <string>
#include <cctype>

class BitcoinExchange
{
    private:
        std::map<std::string, double> _rates;
        void _readDatabase();
        bool _validateDate(std::string const &date);
        double _validatePrice(std::string const &price);
        void _multiplyWithRate(std::string const &date, double price);

    public:
        BitcoinExchange();
        BitcoinExchange(BitcoinExchange const &oth);
        BitcoinExchange &operator=(BitcoinExchange const &oth);
        ~BitcoinExchange();

        std::map<std::string, double> const &getRates() const;
        void execute(char const *fileName);

        class CouldNotOpenFile : public std::exception
        {
            public:
                virtual const char *what() const throw()
                {
                    return ("Could not open file");
                }
        };

         class InvalidColumnFormat : public std::exception
        {
            public:
                virtual const char *what() const throw()
                {
                    return ("Invalid column header format.");
                }
        };

        class InvalidDateFormat : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					return ("Invalid date format. Expected 'YYYY-MM-DD'");
				}
		};

        class InvalidPriceFormat : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					return ("Invalid price format. Expected a number between 0.0 and 1000.0");
				}
		};

};

#endif