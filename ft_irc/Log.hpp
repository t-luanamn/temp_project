#ifndef LOG_HPP
# define LOG_HPP

# include <iostream>
# include <string>

# define RESET    "\033[0;0m"
# define RED      "\033[0;31m"
# define GREEN    "\033[0;32m"
# define YELLOW   "\033[0;33m"
# define BLUE     "\033[0;34m"
# define MAGENTA  "\033[0;35m"
# define CYAN     "\033[0;36m"
# define WHITE    "\033[0;37m"

class Log
{
  public:
    Log(void);
    Log(const Log &rhs);
    ~Log(void);
    Log &operator=(const Log &rhs);

    // Normal color
    void outN(const std::string& message);

    // Color text
    void out(const std::string& message, std::string color = RESET);
};

#endif