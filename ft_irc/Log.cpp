#include "Log.hpp"

Log::Log(void)
{
}

Log::Log(const Log &rhs)
{
  (void)rhs;
}

Log::~Log(void)
{
}

Log &Log::operator=(const Log &rhs)
{
  (void)rhs;
  return *this;
}

void Log::outN(const std::string& message)
{
    std::cout << message << std::endl;
}

void Log::out(const std::string& message, std::string color)
{
    std::cout << color << message << RESET << std::endl;
}

int main(void)
{
    Log log;

    log.outN("Hello World!");
    log.out("Hello World!", RED);
    log.out("Hello World!", GREEN);
    log.out("Hello World!", YELLOW);
    log.out("Hello World!", BLUE);
    log.out("Hello World!", MAGENTA);
    log.out("Hello World!", CYAN);
    log.out("Hello World!", WHITE);

    return (0);
}



/*
class Log
{
public:
	Log();
	~Log();
	Log(const Log &rhs);
	Log operator=(const Log &rhs);
	static void out(const std::string &message, std::string color = NONE);
	static void out(const int number, std::string color = NONE);
	static void out(const double number, std::string color = NONE);
	static void out(const float number, std::string color = NONE);
	static void nl(const std::string &message = "", std::string color = NONE);
	static void nl(const int number, std::string color = NONE);
	static void nl(const double number, std::string color = NONE);
	static void nl(const float number, std::string color = NONE);
	static void	setColor(std::string color = NONE);
};

Log::Log()
{
}

Log::~Log()
{
}

Log::Log(const Log &rhs)
{
	(void)rhs;
}

Log Log::operator=(const Log &rhs)
{
	(void)rhs;
	return *this;
}

void Log::out(const std::string &message, std::string color) 
{
	std::cout << color << message << NONE;
}

void Log::out(const int number, std::string color) 
{
	std::cout << color << number << NONE;
}

void Log::out(const double number, std::string color)
{
	std::cout << color << number << NONE;
}

void Log::out(const float number, std::string color) 
{
	std::cout << color << number << NONE;
}

void Log::nl(const std::string &message, std::string color) 
{
	std::cout << color << message << NONE << std::endl;
}

void Log::nl(const int number, std::string color) 
{
	std::cout << color << number << NONE << std::endl;
}

void Log::nl(const double number, std::string color)
{
	std::cout << color << number << NONE << std::endl;
}

void Log::nl(const float number, std::string color) 
{
	std::cout << color << number << NONE << std::endl;
}

void Log::setColor(std::string color)
{
	std::cout << color;
}
*/