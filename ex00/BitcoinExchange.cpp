#include "BitcoinExchange.hpp"


// trim from start (left)
std::string ltrim(const std::string &s) {
    size_t start = 0;
    while (start < s.length() && isspace(s[start])) start++;
    return s.substr(start);
}

// trim from end (right)
std::string rtrim(const std::string &s) {
    if (s.empty()) return s;
    size_t end = s.length() - 1;
    while (end > 0 && isspace(s[end])) end--;
    return s.substr(0, end + 1);
}

// trim both sides
std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}

BitcoinExchange::BitcoinExchange()
{
    _readDatabase();
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &oth)
{
    if(this != &oth)
    {
        *this= oth;
    }
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &oth)
{
    if(this != &oth)
        this->_rates = oth._rates;
    return (*this);
}

BitcoinExchange::~BitcoinExchange()
{

}



void BitcoinExchange::_readDatabase()
{
    std::ifstream file("data.csv");
    if(!file.is_open())
        throw CouldNotOpenFile();
    
    std::string line;

    std::getline(file, line);
    if(line != "date,exchange_rate")
        throw InvalidColumnFormat();
    
    while(std::getline(file,line))
    {
        std::string date,price;
        std::istringstream iss(line);
       getline(iss, date, ',');
        getline(iss, price, ',');
        date = trim(date);
        price = trim(price);

        double priceValue;
        std::istringstream priceStream(price);
        if(!(priceStream >> priceValue))
            throw InvalidPriceFormat();
        _rates[date] = priceValue;
    
    }
    file.close();
}




void BitcoinExchange::execute(char const *fileName)
{
    std::ifstream file(fileName);
    if(!file.is_open())
        throw CouldNotOpenFile();

    std::string line;
    std::getline(file, line);
    if (trim(line) != "date | value") 
        throw InvalidColumnFormat();

    while(std::getline(file, line))
    {
        if (trim(line).empty())
            continue; // skip empty lines

        std::string date, valueStr;
        double priceValue;
        std::istringstream ss(line);
        std::getline(ss, date, '|');
        std::getline(ss, valueStr, '|');

        date = trim(date);
        valueStr = trim(valueStr);

        if (!_validateDate(date))
        {
            std::cout << "Error: bad input => " << date << std::endl;
            continue;
        }

        priceValue = _validatePrice(valueStr);
        if (priceValue != -1)
            _multiplyWithRate(date, priceValue);
    } 
}



bool BitcoinExchange::_validateDate(const std::string &date)
{
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    for (int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7) continue;
        if (!isdigit(date[i])) return false;
    }

    int year  = std::stoi(date.substr(0,4));
    int month = std::stoi(date.substr(5,2));
    int day   = std::stoi(date.substr(8,2));

    if (month < 1 || month > 12) return false;
    if (day < 1) return false;

    int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    bool isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    if (isLeap) daysInMonth[1] = 29;

    if (day > daysInMonth[month - 1]) return false;

    return true;
}


double BitcoinExchange::_validatePrice(const std::string &valueStr)
{
    std::string str = trim(valueStr);
    if (str.empty())
    {
        std::cout << "Error: bad input => " << valueStr << std::endl;
        return -1;
    }

    // Check valid characters: digits and optional single dot
   int dotCount = 0;
for (size_t i = 0; i < str.size(); i++)
{
    if (str[i] == '.')
        dotCount++;
    else if (!isdigit(str[i]) && !(i == 0 && str[i] == '-'))
    {
        std::cout << "Error: bad input => " << valueStr << std::endl;
        return -1;
    }
}
    if (dotCount > 1)
    {
        std::cout << "Error: bad input => " << valueStr << std::endl;
        return -1;
    }

    double price = 0;
    std::istringstream ss(str);
    if (!(ss >> price) || price < 0)
    {
        std::cout << "Error: not a positive number." << std::endl;
        return -1;
    }
    if (price > 1000)
    {
        std::cout << "Error: too large a number." << std::endl;
        return -1;
    }

    return price;
}




void BitcoinExchange::_multiplyWithRate(std::string const &date, double price)
{
    std::map<std::string, double>::iterator it = _rates.find(date);
    if (it != _rates.end())
    {
        // Exact date found
        std::cout << date << " => " << price << " = " << price * it->second << std::endl;
        return;
    }

    // Date not found: find closest previous date
    std::map<std::string, double>::iterator it2 = _rates.lower_bound(date);

    if (it2 == _rates.begin())
    {
        // No lower date exists
        std::cout << "Error: no rate available for this date." << std::endl;
        return;
    }

    if (it2 == _rates.end() || it2->first != date)
        --it2; // go to previous date if exact not found

    // std::cout << date << " => " << price << " = "
    //       << std::fixed << std::setprecision(2) << price * it2->second << std::endl;
     std::cout << date << " => " << price << " = "
          << std::fixed<< std::setprecision(1) << price * it2->second << std::endl;
}
